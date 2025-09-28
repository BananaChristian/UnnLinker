#include "parser.hpp"
#include "elf.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

/**
 *@brief Constructor for the parser class
 */
Parser::Parser() {}

/**
 * @brief Parses a single ELF object file and prints its sections.
 * @param filename Path to the ELF object file.
 */
void Parser::parseObj(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return;
    }

    Elf64_Ehdr header{};
    file.read(reinterpret_cast<char *>(&header), sizeof(header));
    if (!file || file.gcount() != sizeof(header)) {
        std::cerr << "[FATAL] Failed to read ELF header!\n";
        return;
    }

    // Verify ELF magic
    if (std::memcmp(header.e_ident, "\x7f"
                                    "ELF",
                    4) != 0)
    {
        std::cerr << "Not a valid ELF file!\n";
        return;
    }
    
    // Sanity checks
    if (header.e_shoff == 0 || header.e_shnum == 0 || header.e_shstrndx >= header.e_shnum) {
        std::cerr << "[FATAL] Invalid section header info!\n";
        return;
    }
    if (header.e_shnum > 10000) {
        std::cerr << "[FATAL] Unreasonably large number of sections: " << header.e_shnum << "\n";
        return;
    }

    // Read all section headers
    std::vector<Elf64_ShdrRaw> sections(header.e_shnum);
    file.seekg(header.e_shoff, std::ios::beg);
    file.read(reinterpret_cast<char *>(sections.data()), header.e_shnum * sizeof(Elf64_ShdrRaw));
    if (!file || file.gcount() != header.e_shnum * sizeof(Elf64_ShdrRaw)) {
        std::cerr << "[FATAL] Failed to read section headers!\n";
        return;
    }

    // Read section header string table
    const Elf64_ShdrRaw &shstrtab_hdr = sections[header.e_shstrndx];
    if (shstrtab_hdr.sh_size == 0) {
        std::cerr << "[FATAL] Section header string table is empty!\n";
        return;
    }

    std::vector<char> shstrtab_data(shstrtab_hdr.sh_size);
    file.seekg(shstrtab_hdr.sh_offset, std::ios::beg);
    file.read(shstrtab_data.data(), shstrtab_hdr.sh_size);
    if (!file || file.gcount() != shstrtab_hdr.sh_size) {
        std::cerr << "[FATAL] Failed to read section header string table!\n";
        return;
    }

    // Print section names
    std::cout << "\n--- Sections ---\n";
    for (size_t i = 0; i < header.e_shnum; ++i) {
        std::string name;
        if (sections[i].sh_name < shstrtab_data.size() && shstrtab_data[sections[i].sh_name] != '\0') {
            name = std::string(&shstrtab_data[sections[i].sh_name]);
        } else {
            name = "<invalid>";
            std::cerr << "Invalid section name for index " << i << ", sh_name: " << sections[i].sh_name << "\n";
        }
        std::cout << "[" << i << "] " << name << "\n";
    }
}

/**
 * @brief Placeholder: generates symbols vector for linker.
 * @return Empty vector for now.
 */
std::vector<Symbol> Parser::generateSymbolsVector()
{
    return std::vector<Symbol>{};
}