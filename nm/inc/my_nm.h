/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** my_nm.h
*/

#ifndef __MY_NM_H__
#define __MY_NM_H__

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>

typedef struct {
    void *data;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
    size_t fsize;
    void *section_table;
} elf_t;

typedef struct symbol_table_info_s {
    Elf64_Shdr *table;
    Elf64_Sym *symbol_table;
    char *string_table;
    int entsize;
} symtab_info_t;

int launcher(char *filename);
void my_nm(elf_t *elf);
char get_symbol(const Elf64_Sym sym, const Elf64_Shdr *shdr);

#endif // __MY_NM_H__