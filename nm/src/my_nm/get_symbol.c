/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** get_symbol.c
*/

#include "my_nm.h"

// missing : G I S -
char get_symbol(const Elf64_Sym sym, const Elf64_Shdr *shdr)
{
    char  c;

    if (sym.st_info == STT_FILE)
        c = 'F';
    else if (sym.st_info == STT_NOTYPE)
        c = 'N';
    else if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        c = 'u';
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
        c = 'W';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'w';
    }
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK
    && ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) {
        c = 'V';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'v';
    }
    else if (sym.st_shndx == SHN_UNDEF)
        c = 'U';
    else if (sym.st_shndx == SHN_ABS)
        c = 'A';
    else if (sym.st_shndx == SHN_COMMON)
        c = 'C';
    else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
    && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'B';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
    && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
        c = 'R';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
    && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
    && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        c = 'T';
    else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
        c = 'D';
    else
        c = '?';
    if (c != '?' && ELF64_ST_BIND(sym.st_info) == STB_LOCAL)
        c += 32;
    return (c);
}