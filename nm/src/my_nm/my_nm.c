/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** my_nm.c
*/

#include "my_nm.h"

static void print_symtab(const Elf64_Shdr *shdr, const symtab_info_t symtab)
{
    char sym_char;

    for (int ctr = 0; symtab.table && ctr < symtab.entsize; ctr += 1) {
        if (symtab.symbol_table[ctr].st_name != 0) {
            sym_char = get_symbol(symtab.symbol_table[ctr], shdr);
            if (sym_char == 'f')
                continue;
            if (sym_char == 'U')
                printf("%*c", 16, ' ');
            else
                printf("%016lx", symtab.symbol_table[ctr].st_value);
            printf(" %c ", sym_char);
            printf("%s\n", &symtab.string_table[symtab.symbol_table[ctr].st_name]);
        }
    }
}

void my_nm(const elf_t *elf)
{
    void *section_strtab = (void*)((char*)elf->ehdr + elf->shdr[elf->ehdr->e_shstrndx].sh_offset);
    symtab_info_t symtab = {NULL, NULL, NULL, 0};
    symtab_info_t dynsym = {NULL, NULL, NULL, 0};

    for (int ctr = 0; ctr < elf->ehdr->e_shnum; ctr += 1) {
        if (elf->shdr[ctr].sh_type == SHT_SYMTAB) {
            symtab.table = &elf->shdr[ctr];
            symtab.symbol_table = (Elf64_Sym*)((char*)(elf->data) + elf->shdr[ctr].sh_offset);
            symtab.entsize = elf->shdr[ctr].sh_size / elf->shdr[ctr].sh_entsize;
        } else if (elf->shdr[ctr].sh_type == SHT_DYNSYM) {
            dynsym.table = &elf->shdr[ctr];
            dynsym.symbol_table = (Elf64_Sym*)((char*)(elf->data) + elf->shdr[ctr].sh_offset);
            dynsym.entsize = elf->shdr[ctr].sh_size / elf->shdr[ctr].sh_entsize;
        } else if (elf->shdr[ctr].sh_type == SHT_STRTAB
        && strcmp((char*)(&section_strtab[elf->shdr[ctr].sh_name]), ".strtab") == 0)
            symtab.string_table = (char*)((char*)(elf->data) + elf->shdr[ctr].sh_offset);
        else if (elf->shdr[ctr].sh_type == SHT_STRTAB
        && strcmp((char*)(&section_strtab[elf->shdr[ctr].sh_name]), ".dynstr") == 0)
            dynsym.string_table = (char*)((char*)(elf->data) + elf->shdr[ctr].sh_offset);
    }
    print_symtab(elf->shdr, symtab);
    print_symtab(elf->shdr, dynsym);
}