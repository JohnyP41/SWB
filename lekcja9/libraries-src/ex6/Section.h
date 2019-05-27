#ifndef _SECTION_H_
#define _SECTION_H_

#include <memory>
#include <elf.h>
#include <string>

typedef uint64_t SectionID;
#define MAKE_SECTION_ID(FILE_ID, SEC_NDX) ((((SectionID) FILE_ID) << 32) | (SEC_NDX))
#define FILE_ID(SECTION_ID) ((uint32_t) ((SECTION_ID) >> 32))
#define SEC_NDX(SECTION_ID) ( (uint32_t) (((1ULL << 32) - 1) & (SECTION_ID)) )

struct Section
{
	SectionID sectionId;

	Elf64_Word type;
	Elf64_Xword flags;
	Elf64_Off offset;
	Elf64_Xword addralign;
	Elf64_Xword size;
	std::string name;

	std::shared_ptr<uint8_t> data;

	Elf64_Word link; // contains sh_link field
	Elf64_Word info; // contains sh_info field
};

#endif /* _SECTION_H_ */
