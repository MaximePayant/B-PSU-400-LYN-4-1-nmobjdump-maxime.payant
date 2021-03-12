/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** main.c
*/

#include "my_objdump.h"

int main(int ac, char **av)
{
    int check = 0;

    if (ac < 2)
        check = launcher("a.out");
    for (int ctr = 1; av[ctr] != NULL; ctr += 1)
        check = (launcher(av[ctr]) ? 84 : check);
    return (check);
}