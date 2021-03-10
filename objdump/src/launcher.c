/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** launcher.c
*/

#include "my_objdump.h"

static void file_error(const char *filename)
{
    switch (errno) {
        case ENOENT:
            fprintf(stderr, "objdump: '%s': No such file\n", filename);
            break;
        default:
            fprintf(stderr, "objdump: %s: %s\n", filename, strerror(errno));
    }
}

static void *extract_file(const char *filename, size_t *size)
{
    void *result;
    struct stat st_buf;
    int fd;

    if (lstat(filename, &st_buf) == -1)
        return (file_error(filename), (void*)-1);
    *size = st_buf.st_size;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (file_error(filename), (void*)-1);
    result = mmap(NULL, st_buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (result == MAP_FAILED)
        return (fprintf(stderr, "objdump: %s: %s\n",
                filename, strerror(errno)), (void*)-1);
    return (result);
}

static bool check_header_type(const unsigned char ident[16],
const char *filename)
{
    if (ident[EI_MAG0] == ELFMAG0
    && ident[EI_MAG1] == ELFMAG1
    && ident[EI_MAG2] == ELFMAG2
    && ident[EI_MAG3] == ELFMAG3)
        return (true);
    fprintf(stderr, "objdump: %s: file format not recognized\n", filename);
    return (false);
}

static elf_t *fill_elf_struct(const char *filename)
{
    elf_t *elf = malloc(sizeof(elf_t));

    if (!elf)
        return (NULL);
    elf->data = extract_file(filename, &(elf->fsize));
    if (elf->data == (void*)-1)
        return (free(elf), NULL);
    elf->ehdr = (Elf64_Ehdr*)(elf->data);
    if (!check_header_type(elf->ehdr->e_ident, filename))
        return (free(elf), NULL);
    elf->shdr = (Elf64_Shdr*)((char*)(elf->ehdr) + elf->ehdr->e_shoff);
    elf->section_table =
    (char*)elf->data + elf->shdr[elf->ehdr->e_shstrndx].sh_offset;
    return (elf);
}

int launcher(const char *filename)
{
    elf_t *elf = fill_elf_struct(filename);

    if (elf) {
        printf("\n%s:     ", filename);
        my_objdump(elf);
        munmap(elf->data, elf->fsize);
        free(elf);
        return (0);
    }
    return (84);
}