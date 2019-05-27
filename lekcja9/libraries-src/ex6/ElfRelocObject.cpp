#include "ElfRelocObject.h"
#include "Section.h"
#include "Symbol.h"
#include "Debug.h"

#include <cstdio>
#include <stdexcept>
#include <memory>

ElfRelocObject::ElfRelocObject(uint32_t fileId) : fileId(fileId)
{
}

bool ElfRelocObject::IsRelocatable(const Elf64_Ehdr& ehdr)
{
	if (ehdr.e_ident[EI_MAG0] != ELFMAG0)
		return false;
	if (ehdr.e_ident[EI_MAG1] != ELFMAG1)
		return false;
	if (ehdr.e_ident[EI_MAG2] != ELFMAG2)
		return false;
	if (ehdr.e_ident[EI_MAG3] != ELFMAG3)
		return false;
	if (ehdr.e_type != ET_REL)
		return false;
	return true;
}

void ElfRelocObject::Load(FILE * f)
{
	Elf64_Ehdr ehdr;
	fread(&ehdr, sizeof(Elf64_Ehdr), 1, f);
	if (! IsRelocatable(ehdr))
	{
		throw std::runtime_error("This is not a relocatable ELF file!");
	}

	fseek(f, ehdr.e_shoff, SEEK_SET);
	Elf64_Shdr * shdrs = new Elf64_Shdr[ehdr.e_shnum];

	if (fread(shdrs, sizeof(Elf64_Shdr), ehdr.e_shnum, f) != ehdr.e_shnum)
	{
		throw std::runtime_error("Error while loading sections' headers.");
	}

	/* read section containing info about sections' names */
	Elf64_Shdr * secNamesSectionHdr = shdrs + ehdr.e_shstrndx;
	char * secStrTab = new char[secNamesSectionHdr->sh_size];
	fseek(f, secNamesSectionHdr->sh_offset, SEEK_SET);
	fread(secStrTab, secNamesSectionHdr->sh_size, 1, f);

	for (unsigned i = 0; i < ehdr.e_shnum; ++i)
	{
		Elf64_Shdr * shdr = shdrs + i;
		Section section;
		section.sectionId = MAKE_SECTION_ID(fileId, i);
		section.type = shdr->sh_type;
		section.flags = shdr->sh_flags;
		section.offset = shdr->sh_offset;
		section.addralign = shdr->sh_addralign;
		section.info = shdr->sh_info;
		section.link = shdr->sh_link;
		//!!
		//section.addralign = 0x100;
		//!!
		section.size = shdr->sh_size;
		section.name = std::string(secStrTab + shdr->sh_name);
		printf("section.name = %s\n", section.name.c_str());
		if (section.type != SHT_NOBITS)
		{
			section.data = std::shared_ptr<uint8_t>(new uint8_t[shdr->sh_size],
				[](uint8_t * p) { delete [] p; } );

			fseek(f, shdr->sh_offset, SEEK_SET);
			fread(section.data.get(), section.size, 1, f);
		}

		sections.push_back(section);
	}

	/* load symbols */
	for (unsigned i = 0; i < ehdr.e_shnum; ++i)
	{
		Elf64_Shdr * shdr = shdrs + i;
		if (shdr->sh_type == SHT_SYMTAB)
		{
			Section& strSec = sections[shdr->sh_link];
			LOG("strSec's name: %s\n", strSec.name.c_str());
			char * strtab = reinterpret_cast<char*>(strSec.data.get());

			uint8_t * secData = sections[i].data.get();
			Elf64_Xword secSize = sections[i].size;
			Elf64_Sym * sym = (Elf64_Sym*) (secData);
			for (; (uint8_t *) sym < secData + secSize; sym++)
			{
				if (! (ELF64_ST_TYPE(sym->st_info) == STT_NOTYPE
					&& sym->st_shndx == SHN_UNDEF))
				{
					Symbol symbol;
					if (sym->st_name != 0)
					{
						symbol.name = strtab + sym->st_name;
					}
					symbol.value = sym->st_value;
					symbol.info = sym->st_info;
					symbol.sectionId = MAKE_SECTION_ID(fileId, sym->st_shndx);
					symbol.size = sym->st_size;
					symbols.push_back(symbol);
					LOG("Symbol name: %s", (char*)strtab + sym->st_name);
				}
			}
		}
	}

	delete [] secStrTab;
	delete [] shdrs;
}

const std::vector<Section>& ElfRelocObject::GetSections()
{
	return sections;
}

const std::vector<Symbol>& ElfRelocObject::GetSymbols()
{
	return symbols;
}
