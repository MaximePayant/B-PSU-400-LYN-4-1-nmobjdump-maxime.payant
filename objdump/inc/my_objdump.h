/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** my_objdump.h
*/

#ifndef __MY_OBJDUMP_H__
#define __MY_OBJDUMP_H__

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

int launcher(const char *filename);
void my_objdump(const elf_t *elf);
void print_header(const elf_t *elf);
void print_section_content(const void *data, const Elf64_Shdr *shdr);

#endif // __MY_OBJDUMP_H__