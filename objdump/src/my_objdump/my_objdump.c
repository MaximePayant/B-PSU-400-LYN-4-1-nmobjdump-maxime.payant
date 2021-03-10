/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** my_objdump.c
*/

#include "my_objdump.h"

static const char *flags_names[5] = {
    "EXEC_P",
    "DYNAMIC",
    "HAS_RELOC",
    "D_PAGED",
    "HAS_SYM"
};

static uint32_t check_flags(const elf_t *elf, bool (*flags)[5], int *count)
{
    uint32_t flag_value = 0;

    (*flags)[0] = (elf->ehdr->e_type == ET_EXEC ? *count += 1,
                (flag_value |= (unsigned)0x02), true : false);
    (*flags)[1] = (elf->ehdr->e_type == ET_DYN ? *count += 1,
                (flag_value |= (unsigned)0x40), true : false);
    (*flags)[2] = (elf->ehdr->e_type == ET_REL ? *count += 1,
                (flag_value |= (unsigned)0x01), true : false);
    (*flags)[3] = (elf->ehdr->e_phnum ? *count += 1,
                (flag_value |= (unsigned)0x100), true : false);
    for (int ctr = 0; ctr < elf->ehdr->e_shnum; ctr++)
        if (elf->shdr[ctr].sh_type == SHT_SYMTAB
        || elf->shdr[ctr].sh_type == SHT_DYNSYM) {
            (*flags)[4] = true;
            flag_value |= (unsigned)0x10;
            *count += 1;
            break;
        }
    return (flag_value);
}

static void print_header(const elf_t *elf)
{
    bool flags[5] = {false, false, false, false, false};
    int count = 0;
    uint32_t flag_value = check_flags(elf, &flags, &count);

    printf("file format elf64-x86-64\n");
    printf("architecture: i386:x86-64, flags 0x%08x:\n", flag_value);
    for (int ctr = 0; ctr < 5; ctr += 1)
        if (flags[ctr]) {
            printf("%s", flags_names[ctr]);
            count -= (count > 1 ? printf(", "), 1 : printf("\n"));
        }
    printf("start address 0x%016lx\n\n", elf->ehdr->e_entry);
}

static void print_section_content(const void *data, const Elf64_Shdr *shdr)
{
    Elf64_Addr addr = shdr->sh_addr;
    unsigned char c;

    for (Elf64_Xword ctr = 0; ctr < shdr->sh_size;) {
        if (ctr % 16 == 0)
            printf(" %04lx ", addr);
        for (int i = 0; i < 16; i += 1) {
            if (ctr + i < shdr->sh_size) {
                c = ((char*)data + shdr->sh_offset)[(int)ctr + i];
                printf("%02x", c);
            }
            else
                printf("  ");
            if ((i + 1) % 4 == 0)
                printf(" ");
        }
        printf(" ");
        for (int i = 0; i < 16 && ctr + i < shdr->sh_size; i += 1) {
            c = ((char*)data + shdr->sh_offset)[(int)ctr + i];
            c >= 32 && c <= 126 ? printf("%c", c) : printf(".");
        }
        ctr += 16;
        addr += 16;
        printf("\n");
    }
}

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