/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** get_symbol.c
*/

#include "my_nm.h"

/*

[0161 : x : 0001 : 0002] -> u

[0018 : 0000] -> U (pas disp %016)

[0034 : 0000]
[0032 : 0000] -> w (pas disp %016)

[0032 : x : 0001 : 0003] -> W

[0000 : x : 0001 : 0002]
[0001 : x : 0001 : 0002]
[0001 : x : 0007 : 0002] -> r

[0017 : x : 0001 : 0002] -> R

[0002 : x : 0001 : 0006] -> t

[0001 : x : 0008 : 0003] -> b

[0017 : x : 0008 : 0003]
[0016 : x : 0008 : 0003] -> B

[0000 : x : 0014 : 0003]
[0001 : x : 0001 : 0003]
[0001 : x : 0006 : 0003]
[0001 : x : 0014 : 0003]
[0001 : x : 0015 : 0003] -> d

[0017 : x : 0001 : 0003]
[0016 : x : 0001 : 0003] -> D

[0018 : x : 0001 : 0006] -> T

[0033 : x : 0001 : 0003] -> V

*/

char get_symbol(const Elf64_Sym sym, const Elf64_Shdr *shdr)
{
    if (sym.st_info == STT_FILE)
        return ('f');
    if (sym.st_info == 161)
        return ('u');
    if (sym.st_info == 18) {
        if (sym.st_shndx == 0)
            return ('U');
        return ('T');
    }
    if (sym.st_info == 34)
        return ('w');
    if (sym.st_info == 32) {
        if (sym.st_shndx == 0)
            return ('w');
        return ('W');
    }
    if (sym.st_info == 0) {
        if (shdr[sym.st_shndx].sh_flags == 2)
            return ('r');
        return ('d');
    }
    if (sym.st_info == 1) {
        if (shdr[sym.st_shndx].sh_flags == 2)
            return ('r');
        else if (shdr[sym.st_shndx].sh_type == 8)
            return ('b');
        return ('d');
    }
    if (sym.st_info == 17) {
        if (shdr[sym.st_shndx].sh_flags == 2)
            return ('R');
        else if (shdr[sym.st_shndx].sh_type == 8)
            return ('B');
        return ('D');
    }
    if (sym.st_info == 2)
        return ('t');
    if (sym.st_info == 16) {
        if (sym.st_shndx == 8)
            return ('r');
        return ('d');
    }
    if (sym.st_info == 33)
        return ('V');
    return ('?');
}

/*
char get_symbol(const Elf64_Sym sym, const Elf64_Shdr *shdr)
{
    char  c;
    //printf("[%04u", sym.st_info);
    //printf(" : %04u", sym.st_shndx);
    //if (sym.st_shndx && sym.st_info != STT_FILE) {
    //    printf(" : %04u", shdr[sym.st_shndx].sh_type);
    //    printf(" : %04lu]\n", shdr[sym.st_shndx].sh_flags);
    //}
    //else
    //    printf("]\n");

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
*/