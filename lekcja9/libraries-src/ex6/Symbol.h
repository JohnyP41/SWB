#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <memory>
#include <elf.h>

struct Symbol
{
	std::string name;
	Elf64_Addr value;
	unsigned char info;
	//unsigned char type;
	//unsigned char bind;
	Elf64_Xword size; /* used only for SHN_COMMON */
	SectionID sectionId;
};

#endif /* _SYMBOL_H_ */
