#include <map>
#include <vector>

#include "Section.h"
#include "Symbol.h"

class ElfRelocObject; // fwd decl

typedef uint64_t Offset;
struct FVOffset
{
	Offset file; /* offset in file */
	Offset virt; /* offset in virtual memory */
};
typedef std::map<SectionID, FVOffset> OffsetMap;

class ElfExecutable
{
	private:
	std::vector<Section> reSections;
	std::vector<Section> rwSections;
	std::vector<Section> rweSections;

	std::vector<Section> allSections;
	std::vector<Symbol> allSymbols;

	OffsetMap sec2off;
	Symbol entryPoint;

	bool executableStack;


	FVOffset Layout(std::vector<Section> &secVector, FVOffset start);
	void AllocateCommonSymbols();

	Elf64_Ehdr GetEhdr(Offset entry, Offset phoff, Offset shoff,
		uint16_t phnum, uint16_t shnum);
	Elf64_Phdr GetPhdr(const std::vector<Section>& sections, Elf64_Word flags);
	Elf64_Shdr GetShdr(Section * section);
	Elf64_Xword GetLengthInFile(const std::vector<Section>& sections);
	Elf64_Xword GetLengthInMemory(const std::vector<Section>& sections);
	void MakeFVOffsetsCongruent(FVOffset& offsets);
	FVOffset GetSymbolOffset(SectionID sectionId, Offset value);

	Section GetSection(const SectionID sectionId);
	Section GetSection(uint32_t fileId, uint32_t sectionNdx);

	unsigned WritePhdrs(FILE * f);
	void WriteSectionsData(FILE * f, std::vector<Section>& sections);
	unsigned WriteShdrs(FILE * f, std::vector<Section>& sections);
	unsigned WriteNullSectionHeader(FILE * f);

	public:
	ElfExecutable();
	bool Add(ElfRelocObject *o);
	void Layout();
	void ProcessRelocations();
	void Write(FILE * f);
};

