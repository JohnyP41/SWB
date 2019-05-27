#include <elf.h>
#include <climits>
#include <cassert>
#include <stdexcept>
#include <string>
#include <algorithm>


#include "ElfExecutable.h"
#include "ElfRelocObject.h"
#include "Section.h"
#include "Symbol.h"
#include "Debug.h"


#define PAGE_SIZE 4096
#define PROGRAM_HEADERS_MAX 4

#define INVALID_SECTION_ID  ((SectionID) 0)

ElfExecutable::ElfExecutable() : executableStack(false) {}

bool ElfExecutable::Add(ElfRelocObject *o)
{
	// iterate through sections in o:
	const std::vector<Section>& sections = o->GetSections();
	for (std::vector<Section>::const_iterator section = sections.begin();
		section != sections.end(); section++)
	{
		if (section->flags & SHF_ALLOC)
		{
			if ((section->flags & SHF_EXECINSTR)
				&& (section->flags & SHF_WRITE))
			{
				rweSections.push_back(*section);
				LOG("Adding to rweSections: %s", section->name.c_str());
			}
			else if (section->flags & SHF_EXECINSTR)
			{
				reSections.push_back(*section);
				LOG("Adding to reSections: %s", section->name.c_str());
			}
			else
			{
				rwSections.push_back(*section);
				LOG("Adding to rwSections: %s", section->name.c_str());
			}
		}
		allSections.push_back(*section);
	}
	
	/* find out if code in this object file requires an executable stack */
	bool noexecStackFound = false;
	for (std::vector<Section>::const_iterator section = sections.begin();
		section != sections.end(); section++)
	{
		if (section->name == ".note.GNU-stack")
		{
			noexecStackFound = true;
		}
	}
	if (! noexecStackFound)
		executableStack = true;
	
	/* find potential entry point */
	const std::vector<Symbol>& symbols = o->GetSymbols();
	for (const Symbol& symbol : symbols)
	{
		if (ELF64_ST_BIND(symbol.info) == STB_GLOBAL
			&& symbol.name == "_start")
		{
			entryPoint = symbol;
		}
	}

	/* copy all symbols to our local "symbol storage" */
	allSymbols.insert(allSymbols.end(), symbols.begin(), symbols.end());
}

void ElfExecutable::Layout()
{
	/* First, allocate space for SHN_COMMON symbols. */
	AllocateCommonSymbols();

	FVOffset len = {0}, ret;
	len.file = sizeof(Elf64_Ehdr) + PROGRAM_HEADERS_MAX * sizeof(Elf64_Phdr);
	len.virt = 0x400000;
	/* make first section's file offset and vaddr congruent mod PAGE_SIZE */
	MakeFVOffsetsCongruent(len);

	ret = Layout(reSections, len);
	len.file += ret.file;
	len.virt += ret.virt;
	/* make next section's file offset and vaddr congruent mod PAGE_SIZE */
	MakeFVOffsetsCongruent(len);

	ret = Layout(rwSections, len);
	len.file += ret.file;
	len.virt += ret.virt;
	/* make next section's file offset and vaddr congruent mod PAGE_SIZE */
	MakeFVOffsetsCongruent(len);

	ret = Layout(rweSections, len);
	len.file += ret.file;
	len.virt += ret.virt;
}

void ElfExecutable::ProcessRelocations()
{
	for (auto& section : allSections)
	{
		/* SHT_REL is nod used in amd64 */
		if (section.type == SHT_RELA)
		{
			const Section symtabSec = GetSection(
				FILE_ID(section.sectionId), section.link);
			assert(symtabSec.sectionId != INVALID_SECTION_ID);

			const Section editSec = GetSection(
				FILE_ID(section.sectionId), section.info);
			assert(editSec.sectionId != INVALID_SECTION_ID);

			const Section strSec = GetSection(
				FILE_ID(symtabSec.sectionId), symtabSec.link);
			assert(strSec.sectionId != INVALID_SECTION_ID);


			Elf64_Sym * symtab = reinterpret_cast<Elf64_Sym*>(symtabSec.data.get());
			char * strtab = reinterpret_cast<char*>(strSec.data.get());

			Elf64_Rela * relaBegin = reinterpret_cast<Elf64_Rela*>(
				section.data.get());
			Elf64_Rela * relaEnd = reinterpret_cast<Elf64_Rela*>(
				section.data.get() + section.size);
			/* iterate through all relocation entries we found */
			for (Elf64_Rela * r = relaBegin; r < relaEnd; r++)
			{
				// ELF64_R_SYM gives an index into symbol table
				Elf64_Sym * sym = symtab + ELF64_R_SYM(r->r_info);
				Offset symVAddr = 0;
				switch (sym->st_shndx)
				{
					case SHN_COMMON:
					case SHN_UNDEF:
					{
						char * sname = strtab + sym->st_name;
						LOG("Found relocation of %s symbol %s",
							(sym->st_shndx == SHN_COMMON) ?  "COMMON" : "UNDEF",
							sname);
						for (const Symbol& symbol : allSymbols)
						{
							if (ELF64_ST_BIND(symbol.info) == STB_GLOBAL
								&& symbol.name == sname)
							{
								symVAddr = GetSymbolOffset(
									symbol.sectionId, symbol.value).virt;
							}
						}
						if (symVAddr == 0)
						{
							fprintf(stderr, "### FATAL: symbol %s not found!\n", sname);
						}
						break;
					}
					default:
					{
						if (sym->st_shndx >= SHN_LORESERVE)
						{
							throw std::runtime_error(
								"st_shndx >= SHN_LORESERVE: not implemented");
						}
						SectionID sectionId = MAKE_SECTION_ID(
							FILE_ID(symtabSec.sectionId), sym->st_shndx);
						symVAddr = GetSymbolOffset(
							sectionId, sym->st_value).virt;

						break;
					}
				}
				switch (ELF64_R_TYPE(r->r_info))
				{
					case R_X86_64_PC32:
					{
						LOG("Patching %s at offset 0x%lx with 0x%lx: ",
							editSec.name.c_str(), r->r_offset, symVAddr);
						int32_t * place = reinterpret_cast<int32_t*>(
						        editSec.data.get() + r->r_offset);
						Offset placeAddr = sec2off[editSec.sectionId].virt + r->r_offset;
						/* At this point we have the following information:
						 * 1. r - the Elf64_Rela structure representing the
						 *    relocation being processed
						 * 2. editSec - the section which is to be modified
						 *    (the one which is pointed by the sh_info field
						 *    of the relevant SHT_RELA section)
						 *    a. editSec.data.get() gives a pointer to the body
						 *       of editSec section
						 * 3. sec2off[editSec.sectionId] - offset of the editSec
						 *    both in file and in memory (see FVOffset struct)
						 * 4. symVAddr - virtual address of the symbol pointed
						 *    by ELF64_R_SYM(r->r_info)
						 * TODO: Write the code which performs relocation r.
						 */
						break;
					}
					default:
						throw std::runtime_error("relocation types other than "
							"R_X86_64_PC32 are not supported");
				}
			}
		}
	}
}

FVOffset ElfExecutable::Layout(std::vector<Section> &secVector, FVOffset start)
{
	FVOffset curr = start;
	for (std::vector<Section>::iterator it = secVector.begin();
			it != secVector.end(); it++)
	{
		Section * sec = &(*it);
		/* align curr accordingly to section's requirement if necessary */
		if (sec->addralign > 1)
		{
			uint64_t alignMask = sec->addralign - 1;
			if (curr.virt & alignMask)
			{
				curr.virt += sec->addralign;
				curr.virt &= (~alignMask);
				/* Although sh_addralign applies only to memory address, it
				 * affects file offset too. However, when kernel loads an ELF
				 * executable memory, kernel just maps chunks of ELF file into
				 * the memory. */
				curr.file += sec->addralign;
				curr.file &= (~alignMask);
			}
		}
		sec2off[sec->sectionId] = curr;
		LOG("Set section %s to offset { file: 0x%lx, virt: 0x%lx }",
			sec->name.c_str(), curr.file, curr.virt);
		curr.file += (sec->type == SHT_NOBITS) ? 0 : sec->size;
		curr.virt += sec->size;
	}
	return curr;
}

Elf64_Ehdr ElfExecutable::GetEhdr(Offset entry, Offset phoff,
	Offset shoff, uint16_t phnum, uint16_t shnum)
{
	Elf64_Ehdr ehdr;
	ehdr.e_ident[EI_MAG0] = ELFMAG0;
	ehdr.e_ident[EI_MAG1] = ELFMAG1;
	ehdr.e_ident[EI_MAG2] = ELFMAG2;
	ehdr.e_ident[EI_MAG3] = ELFMAG3;
	ehdr.e_ident[EI_CLASS] = ELFCLASS64;
	ehdr.e_ident[EI_DATA] = ELFDATA2LSB;
	ehdr.e_ident[EI_VERSION] = EV_CURRENT;
	ehdr.e_ident[EI_OSABI] = ELFOSABI_SYSV;
	ehdr.e_ident[EI_ABIVERSION] = 0;
	ehdr.e_ident[EI_PAD] = 0;
	ehdr.e_ident[EI_NIDENT] = EI_NIDENT;

	ehdr.e_type = ET_EXEC;
	ehdr.e_machine = EM_X86_64;
	ehdr.e_version = EV_CURRENT;
	ehdr.e_entry = entry;
	ehdr.e_phoff = phoff;
	ehdr.e_shoff = shoff;
	ehdr.e_flags = 0;
	ehdr.e_ehsize = sizeof(Elf64_Ehdr);
	ehdr.e_phentsize = sizeof(Elf64_Phdr);
	ehdr.e_phnum = phnum;
	ehdr.e_shentsize = sizeof(Elf64_Shdr);
	ehdr.e_shnum = shnum;
	ehdr.e_shstrndx = SHN_UNDEF;

	return ehdr;
}

Elf64_Phdr ElfExecutable::GetPhdr(const std::vector<Section>& sections,
	Elf64_Word flags)
{
	if (sections.empty())
		return {0};
	Elf64_Phdr phdr;
	phdr.p_type = PT_LOAD;

	FVOffset firstSecOffset = sec2off[sections.front().sectionId];
	phdr.p_offset = firstSecOffset.file;
	phdr.p_vaddr = firstSecOffset.virt;
	phdr.p_paddr = 0;
	phdr.p_filesz = GetLengthInFile(sections);
	phdr.p_memsz = GetLengthInMemory(sections);
	phdr.p_flags = flags;
	phdr.p_align = PAGE_SIZE;

	return phdr;
}

Elf64_Shdr ElfExecutable::GetShdr(Section * section)
{
	Elf64_Shdr shdr;
	shdr.sh_name = 0;
	shdr.sh_type = section->type;
	shdr.sh_flags = section->flags;
	shdr.sh_addr = sec2off[section->sectionId].virt;
	shdr.sh_offset = sec2off[section->sectionId].file;
	shdr.sh_size = section->size;
	shdr.sh_link = 1; /* not used with SHT_PROGBITS nor SHT_NOBITS */
	shdr.sh_info = 2; /* not used with SHT_PROGBITS nor SHT_NOBITS */
	shdr.sh_addralign = section->addralign;
	shdr.sh_entsize = 0; /* not used with SHT_PROGBITS nor SHT_NOBITS */
	return shdr;
}

unsigned ElfExecutable::WritePhdrs(FILE * f)
{
	unsigned phdrsWritten = 0;
	Elf64_Phdr rePhdr = GetPhdr(reSections, PF_R | PF_X);
	Elf64_Phdr rwPhdr = GetPhdr(rwSections, PF_R | PF_W);
	Elf64_Phdr rwePhdr = GetPhdr(rweSections, PF_R | PF_W | PF_X);
	if (rePhdr.p_offset) /* are there any sections in this segment? */
	{
		fwrite(&rePhdr, sizeof(Elf64_Phdr), 1, f);
		phdrsWritten++;
	}
	if (rwPhdr.p_offset) /* are there any sections in this segment? */
	{
		fwrite(&rwPhdr, sizeof(Elf64_Phdr), 1, f);
		phdrsWritten++;
	}
	if (rwePhdr.p_offset) /* are there any sections in this segment? */
	{
		fwrite(&rwePhdr, sizeof(Elf64_Phdr), 1, f);
		phdrsWritten++;
	}
	if (executableStack)
	{
		Elf64_Phdr gnuStackPhdr = {0};
		gnuStackPhdr.p_type = PT_GNU_STACK;
		gnuStackPhdr.p_flags = PF_R | PF_W | PF_X;
		gnuStackPhdr.p_align = 0x10;
		fwrite(&gnuStackPhdr, sizeof(Elf64_Phdr), 1, f);
		phdrsWritten++;
	}
	return phdrsWritten;
}

void ElfExecutable::WriteSectionsData(FILE * f, std::vector<Section>& sections)
{
	for (auto& section : sections)
	{
		if (section.type != SHT_NOBITS)
		{
			const FVOffset& offset = sec2off[section.sectionId];
			fseek(f, offset.file, SEEK_SET);
			fwrite(section.data.get(), section.size, 1, f);
		}
	}
}

unsigned ElfExecutable::WriteShdrs(FILE * f, std::vector<Section>& sections)
{
	unsigned ret = 0;
	for (auto& section : sections)
	{
		Elf64_Shdr shdr = GetShdr(&section);
		ret += fwrite(&shdr, sizeof(Elf64_Shdr), 1, f);
	}
	return ret;
}

unsigned ElfExecutable::WriteNullSectionHeader(FILE * f)
{
	Elf64_Shdr shdr = {0};
	shdr.sh_type = SHT_NULL;
	fwrite(&shdr, sizeof(Elf64_Shdr), 1, f);
	return 1;
}

void ElfExecutable::Write(FILE * f)
{
	Elf64_Xword phdrsOffset = sizeof(Elf64_Ehdr);

	fseek(f, phdrsOffset, SEEK_SET);
	unsigned phdrsWritten = WritePhdrs(f);
	WriteSectionsData(f, reSections);
	WriteSectionsData(f, rwSections);
	WriteSectionsData(f, rweSections);
	Elf64_Xword shdrsOffset = ftell(f);
	unsigned shdrsWritten = WriteNullSectionHeader(f);
	shdrsWritten += WriteShdrs(f, reSections);
	shdrsWritten += WriteShdrs(f, rwSections);
	shdrsWritten += WriteShdrs(f, rweSections);
	fseek(f, 0, SEEK_SET);
	FVOffset entryPointOffset = GetSymbolOffset(
		entryPoint.sectionId, entryPoint.value);
	Elf64_Ehdr ehdr = GetEhdr(entryPointOffset.virt, phdrsOffset, shdrsOffset,
		phdrsWritten, shdrsWritten);
	fwrite(&ehdr, sizeof(Elf64_Ehdr), 1, f);
}

Elf64_Xword ElfExecutable::GetLengthInFile(const std::vector<Section>& sections)
{
	/* TODO needs comment */
	Elf64_Xword ret = 0;
	Offset firstSection = ULLONG_MAX;
	Offset lastSection = 0;
	for (auto section : sections)
	{
		Offset begin = sec2off[section.sectionId].file;
		Offset end = begin + section.size;
		firstSection = std::min(firstSection, begin);
		if (section.type != SHT_NOBITS)
		{
			lastSection = std::max(lastSection, end);
		}
	}
	if (firstSection > lastSection)
	{
		return 0;
	}
	return static_cast<Elf64_Xword>(lastSection - firstSection);
}

Elf64_Xword ElfExecutable::GetLengthInMemory(
	const std::vector<Section>& sections)
{
	Elf64_Xword ret = 0;
	/* Due to sh_align constraint this is not as simple as this:
		for (auto section : sections)
		{
			ret += section.size; 
		}
		return ret;
	   because between sections there may be some alignment padding.
	   So to calculate actual sections' length in memory we return the
	   difference between the end of the last section and the beginning
	   of the first one. */
	if (sections.empty())
	{
		return 0;
	}
	Offset firstSection = ULLONG_MAX;
	Offset lastSection = 0;
	for (auto section : sections)
	{
		Offset begin = sec2off[section.sectionId].virt;
		Offset end = begin + section.size;
		firstSection = std::min(firstSection, begin);
		lastSection = std::max(lastSection, end);
	}
	return static_cast<Elf64_Xword>(lastSection - firstSection);
}

void ElfExecutable::MakeFVOffsetsCongruent(FVOffset& offsets)
{
	uint64_t pgSizeMask = PAGE_SIZE - 1;
	if ((offsets.file & pgSizeMask) > (offsets.virt & pgSizeMask))
	{
		offsets.virt &= (~pgSizeMask);
		offsets.virt |= pgSizeMask & offsets.file;
	}
	else if ((offsets.file & pgSizeMask) < (offsets.virt & pgSizeMask))
	{
		offsets.virt += PAGE_SIZE;
		offsets.virt &= (~pgSizeMask);
		offsets.virt |= pgSizeMask & offsets.file;
	}
}

FVOffset ElfExecutable::GetSymbolOffset(SectionID sectionId, Offset value)
{
	switch (SEC_NDX(sectionId))
	{
		case SHN_UNDEF:
			return {0};
			break;

		case SHN_ABS:
			throw std::runtime_error("not implemented");
			break;

		case SHN_COMMON:
		{
			FVOffset offset = sec2off[MAKE_SECTION_ID(0, SHN_COMMON)];
			offset.virt += value;
			return offset;
			break;
		}

		default:
		{
			FVOffset offset = sec2off[sectionId];
			offset.file += value;
			offset.virt += value;
			return offset;
			break;
		}
	}
}

Section ElfExecutable::GetSection(uint32_t fileId, uint32_t sectionNdx)
{
	return GetSection(MAKE_SECTION_ID(fileId, sectionNdx));
}

Section ElfExecutable::GetSection(const SectionID sectionId)
{
	for (Section& section : allSections)
	{
		if (section.sectionId == sectionId)
			return section;
	}
	Section ret = {0};
	ret.sectionId = INVALID_SECTION_ID;
	return ret;
}

void ElfExecutable::AllocateCommonSymbols()
{
	uint64_t currBoundary = 0;
	for (auto& symbol : allSymbols)
	{
		if (SEC_NDX(symbol.sectionId) == SHN_COMMON)
		{
			/* in SHN_COMMON case symbol.value means alignment */
			uint64_t alignMask = symbol.value - 1;
			if (symbol.value > 0 && (currBoundary & alignMask))
			{
				currBoundary += symbol.value;
				currBoundary &= alignMask;
			}
			/* "rebase" the symbol to the new section */
			symbol.sectionId = MAKE_SECTION_ID(0, SHN_COMMON);
			symbol.value = currBoundary;

			currBoundary += symbol.size;
		}
	}
	if (currBoundary > 0)
	{
		Section commonSection;
		commonSection.type = SHT_NOBITS;
		commonSection.flags = SHF_ALLOC | SHF_WRITE;
		commonSection.offset = 0; /* not used */
		commonSection.addralign = PAGE_SIZE;
		commonSection.size = currBoundary;
		commonSection.name = ".bss";
		commonSection.data = NULL;
		commonSection.link = 0; /* not used */
		commonSection.info = 0; /* not used */
		commonSection.sectionId = MAKE_SECTION_ID(0, SHN_COMMON);
		rwSections.push_back(commonSection);
		allSections.push_back(commonSection);
	}
}

