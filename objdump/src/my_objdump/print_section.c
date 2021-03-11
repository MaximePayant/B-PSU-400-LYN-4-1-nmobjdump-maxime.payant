/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** print_section.c
*/

#include "my_objdump.h"

static void print_hexa_value(Elf64_Xword ctr,
const void *data, const Elf64_Shdr *shdr)
{
    unsigned char c = '\0';

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
}

static void print_char_value(Elf64_Xword ctr,
const void *data, const Elf64_Shdr *shdr)
{
    unsigned char c = '\0';

    for (int i = 0; i < 16 && ctr + i < shdr->sh_size; i += 1) {
        c = ((char*)data + shdr->sh_offset)[(int)ctr + i];
        c >= 32 && c <= 126 ? printf("%c", c) : printf(".");
    }
}

void print_section_content(const void *data, const Elf64_Shdr *shdr)
{
    Elf64_Addr addr = shdr->sh_addr;

    for (Elf64_Xword ctr = 0; ctr < shdr->sh_size; ctr += 16) {
        printf(" %04lx ", addr);
        print_hexa_value(ctr, data, shdr);
        printf(" ");
        print_char_value(ctr, data, shdr);
        printf("\n");
        addr += 16;
    }
}