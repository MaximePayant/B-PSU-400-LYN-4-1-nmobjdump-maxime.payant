/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** main.c
*/

#include "my_objdump.h"

int check_flag(char *str, bool (*flags)[2])
{
    if (strcmp(str, "-f") == 0) {
        (*flags)[0] = true;
        return (1);
    }
    if (strcmp(str, "-s") == 0) {
        (*flags)[1] = true;
        return (1);
    }
    if (strcmp(str, "-sf") == 0
    || strcmp(str, "-fs") == 0) {
        (*flags)[0] = true;
        (*flags)[1] = true;
        return (1);
    }
    return (0);
}

void free_strtab(char **tab)
{
    for (int ctr = 0; tab[ctr]; ctr += 1)
        free(tab[ctr]);
    free(tab);
}

char **parsing(int ac, char **av)
{
    char **result = malloc(sizeof(char*) * ac);
    int result_ctr = 0;
    bool flags[2] = {false, false};

    if (!result) {
        fprintf(stderr, "objdump: Insufficient memory.\n");
        return (NULL);
    }
    for (int ctr = 1; ctr < ac; ctr += 1) {
        if (check_flag(av[ctr], &flags))
            continue;
        result[result_ctr] = strdup(av[ctr]);
        result_ctr += 1;
    }
    result[result_ctr] = NULL;
    if (!flags[0] || !flags[1]) {
        fprintf(stderr, "objdump: Missing flags, need -f and -s.\n");
        return (free_strtab(result), NULL);
    }
    return (result);
}

int main(int ac, char **av)
{
    int check = 0;
    char **filesnames = parsing(ac, av);

    if (!filesnames)
        return (84);
    for (int ctr = 0; filesnames[ctr] != NULL; ctr += 1)
        check = (launcher(filesnames[ctr]) ? 84 : check);
    free_strtab(filesnames);
    return (check);
}