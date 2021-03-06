/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** main.c
*/

#include "my_nm.h"

int main(int ac, char **av)
{
    int check = 0;

    if (ac < 2)
        check = launcher("a.out");
    for (int ctr = 1; av[ctr] != NULL; ctr += 1) {
        if (ac > 2)
            printf("\n%s:\n", av[ctr]);
        check = launcher(av[ctr]);
        if (check != 0)
            break;
    }
    return (check);
}