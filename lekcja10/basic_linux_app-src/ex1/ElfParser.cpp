#include "ElfParser.h"

void ElfParser::parseFile(const std::string &path) {
}

bool ElfParser::isElfFile(const Elf64_Ehdr *header) {
    return header->e_ident[EI_MAG0] == 0x7F && header->e_ident[EI_MAG1] == 'E' && header->e_ident[EI_MAG2] == 'L' && header->e_ident[EI_MAG3] == 'F';
}
