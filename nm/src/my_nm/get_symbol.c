/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** get_symbol.c
*/

#include "my_nm.h"

static char get_symbol_bis(const Elf64_Sym sym)
{
    switch (sym.st_info) {
        case 2:
            return ('t');
        case 16:
            return ((sym.st_shndx == 8 ? 'r' : 'd'));
        case 33:
            return ('V');
    }
    return ('?');
}

char get_symbol(const Elf64_Sym sym, const Elf64_Shdr *shdr)
{
    switch (sym.st_info) {
        case STT_FILE:
            return ('f');
        case 161:
            return ('u');
        case 18:
            return ((sym.st_shndx == 0 ? 'U' : 'T'));
        case 34:
            return ('w');
        case 32:
            return ((sym.st_shndx == 0 ? 'w' : 'W'));
        case 0:
            return ((shdr[sym.st_shndx].sh_flags == 2 ? 'r' : 'd'));
        case 1:
            return ((shdr[sym.st_shndx].sh_flags == 2 ? 'r' :
                    (shdr[sym.st_shndx].sh_type == 8 ? 'b' : 'd')));
    }
    return (get_symbol_bis(sym));
}