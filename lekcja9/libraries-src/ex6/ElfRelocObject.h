#ifndef _ELF_RELOC_OBJECT_H_
#define _ELF_RELOC_OBJECT_H_

#include <cstdio>
#include <vector>
#include <elf.h>

struct Section; // fwd decl
struct Symbol; // fwd decl

class ElfRelocObject
{
	public:
	ElfRelocObject(uint32_t fileId);

	void Load(FILE * f);
	const std::vector<Section>& GetSections();
	const std::vector<Symbol>& GetSymbols();

	protected:
	bool IsRelocatable(const Elf64_Ehdr& ehdr);

	private:
	uint32_t fileId;

	std::vector<Section> sections;
	std::vector<Symbol> symbols;
};

#endif /* _ELF_RELOC_OBJECT_H_ */
