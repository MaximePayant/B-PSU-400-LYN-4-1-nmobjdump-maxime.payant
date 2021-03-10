/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** print_header.c
*/

#include "my_objdump.h"

static const char *flags_names[5] = {
    "HAS_RELOC",
    "EXEC_P",
    "HAS_SYMS",
    "DYNAMIC",
    "D_PAGED"
};

static uint32_t check_flags(const elf_t *elf, bool (*flags)[5], int *count)
{
    uint32_t flag_value = 0;

    (*flags)[1] = (elf->ehdr->e_type == ET_EXEC ? *count += 1,
                (flag_value |= (unsigned)0x02), true : false);
    (*flags)[3] = (elf->ehdr->e_type == ET_DYN ? *count += 1,
                (flag_value |= (unsigned)0x40), true : false);
    (*flags)[0] = (elf->ehdr->e_type == ET_REL ? *count += 1,
                (flag_value |= (unsigned)0x01), true : false);
    (*flags)[4] = (elf->ehdr->e_phnum ? *count += 1,
                (flag_value |= (unsigned)0x100), true : false);
    for (int ctr = 0; ctr < elf->ehdr->e_shnum; ctr++)
        if (elf->shdr[ctr].sh_type == SHT_SYMTAB
        || elf->shdr[ctr].sh_type == SHT_DYNSYM) {
            (*flags)[2] = true;
            flag_value |= (unsigned)0x10;
            *count += 1;
            break;
        }
    return (flag_value);
}

static const char *machine_type(Elf64_Half machine)
{
    switch (machine)
    {
        case EM_M32: return "WE32100";
        case EM_SPARC: return "Sparc";
        case EM_386: return "Intel 80386";
        case EM_68K: return "MC68000";
        case EM_88K: return "MC88000";
        case EM_860: return "Intel 80860";
        case EM_MIPS: return "MIPS R3000";
        case EM_PARISC: return "HPPA";
        case EM_SPARC32PLUS: return "Sparc v8+";
        case EM_PPC: return "PowerPC";
        case EM_PPC64: return "PowerPC64";
        case EM_S390: return "IBM S/390";
        case EM_ARM: return "ARM";
        case EM_SH: return "Renesas / SuperH SH";
        case EM_SPARCV9: return "Sparc v9";
        case EM_IA_64: return "Intel IA-64";
        case EM_NONE: return "None";
        default: return "i386:x86-64";
    }
}

void print_header(const elf_t *elf)
{
    bool flags[5] = {false, false, false, false, false};
    int count = 0;
    uint32_t flag_value = check_flags(elf, &flags, &count);

    if (elf->ehdr->e_ident[EI_CLASS] == ELFCLASS32)
        printf("file format elf32-x86-64\n");
    else
        printf("file format elf64-x86-64\n");
    printf("architecture: %s, flags 0x%08x:\n",
           machine_type(elf->ehdr->e_machine), flag_value);
    for (int ctr = 0; ctr < 5; ctr += 1)
        if (flags[ctr]) {
            printf("%s", flags_names[ctr]);
            count -= (count > 1 ? printf(", "), 1 : printf("\n"), 1);
        }
    if (elf->ehdr->e_ident[EI_CLASS] == ELFCLASS32)
        printf("start address 0x%08lx\n\n", elf->ehdr->e_entry);
    else
        printf("start address 0x%016lx\n\n", elf->ehdr->e_entry);
}