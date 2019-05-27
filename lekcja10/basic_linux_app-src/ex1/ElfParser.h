#ifndef MAIN_APPLICATION_H
#define MAIN_APPLICATION_H

#include <elf.h>
#include <string>

class ElfParser {
public:
    ElfParser() {
    }

    void parseFile(const std::string &path);
private:
    bool isElfFile(const Elf64_Ehdr *header);
};


#endif
