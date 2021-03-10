/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** my_objdump.c
*/

#include "my_objdump.h"

void my_objdump(const elf_t *elf)
{
    void *section_strtab = (void*)((char*)elf->ehdr +
                           elf->shdr[elf->ehdr->e_shstrndx].sh_offset);
    char *tmp = NULL;

    print_header(elf);
    for (int ctr = 0; ctr < elf->ehdr->e_shnum; ctr += 1) {
        tmp = &((char*)section_strtab)[elf->shdr[ctr].sh_name];
        if (!strcmp(tmp, "")
        || !strcmp(tmp, ".bss")
        || !strcmp(tmp, ".symtab")
        || !strcmp(tmp, ".strtab")
        || !strcmp(tmp, ".shstrtab")
        || (!strncmp(tmp, ".rela", 5) && strcmp(tmp, ".rela.dyn")
                                      && strcmp(tmp, ".rela.plt"))
        || !strcmp(tmp, ".note.GNU-stack"))
            continue;
        printf("Contents of section %s:\n", tmp);
        print_section_content(elf->data, &elf->shdr[ctr]);
    }
}