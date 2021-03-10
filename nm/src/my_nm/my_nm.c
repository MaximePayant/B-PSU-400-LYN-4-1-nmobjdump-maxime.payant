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
        if (symtab.symtab[ctr].st_name != 0) {
            sym_char = get_symbol(symtab.symtab[ctr], shdr);
            if (sym_char == 'f')
                continue;
            if (sym_char == 'U')
                printf("%*c", 16, ' ');
            else
                printf("%016lx", symtab.symtab[ctr].st_value);
            printf(" %c ", sym_char);
            printf("%s\n", &symtab.strtab[symtab.symtab[ctr].st_name]);
        }
    }
}

static void check_symtab(const Elf64_Word type,
symtab_info_t *st, Elf64_Shdr *shdr, const void *data)
{
    if (shdr->sh_type == type) {
        st->table = shdr;
        st->symtab = (Elf64_Sym*)((char*)(data) + shdr->sh_offset);
        st->entsize = shdr->sh_size / shdr->sh_entsize;
    }
}

static void check_symtab_strtab(symtab_info_t *st,
const void *section_strtab, Elf64_Shdr *shdr, const void *data)
{
    if (shdr->sh_type == SHT_STRTAB
    && strcmp((char*)(&section_strtab[shdr->sh_name]), ".strtab") == 0)
        st->strtab = (char*)((char*)(data) + shdr->sh_offset);
}

static void check_dynsym_strtab(symtab_info_t *st,
const void *section_strtab, Elf64_Shdr *shdr, const void *data)
{
    if (shdr->sh_type == SHT_STRTAB
    && strcmp((char*)(&section_strtab[shdr->sh_name]), ".dynstr") == 0)
        st->strtab = (char*)((char*)(data) + shdr->sh_offset);
}

void my_nm(const elf_t *elf)
{
    void *section_strtab = (void*)((char*)elf->ehdr +
                           elf->shdr[elf->ehdr->e_shstrndx].sh_offset);
    symtab_info_t symtab = {NULL, NULL, NULL, 0};
    symtab_info_t dynsym = {NULL, NULL, NULL, 0};

    for (int ctr = 0; ctr < elf->ehdr->e_shnum; ctr += 1) {
        check_symtab(SHT_SYMTAB, &symtab, &elf->shdr[ctr], elf->data);
        check_symtab(SHT_DYNSYM, &dynsym, &elf->shdr[ctr], elf->data);
        check_symtab_strtab(&symtab, section_strtab,
                            &elf->shdr[ctr], elf->data);
        check_dynsym_strtab(&dynsym, section_strtab,
                            &elf->shdr[ctr], elf->data);
    }
    print_symtab(elf->shdr, symtab);
    print_symtab(elf->shdr, dynsym);
}