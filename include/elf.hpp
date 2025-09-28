#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdint>

#pragma pack(push, 1)

/**
 * @struct This is a struct that represents the master header
 * @brief The master header size is around 64bytes each field has its own space but total is 64bytes
 */
struct Elf64_Ehdr
{
    unsigned char e_ident[16]; ///< ELF identification
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;
    uint64_t e_phoff;
    uint64_t e_shoff; ///< Section header table offset
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;    ///< Number of section headers
    uint16_t e_shstrndx; ///< Index of section header string table
};
static_assert(sizeof(Elf64_Ehdr) == 64, "Elf64_Ehdr must be exactly 64 bytes");

struct Elf64_ShdrRaw
{
    uint32_t sh_name;
    uint32_t sh_type;
    uint64_t sh_flags;
    uint64_t sh_addr;
    uint64_t sh_offset;
    uint64_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint64_t sh_addralign;
    uint64_t sh_entsize;
};

#pragma pack(pop)