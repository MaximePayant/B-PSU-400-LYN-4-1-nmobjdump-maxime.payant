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
        check = launcher("a.out", ac);
    for (int ctr = 1; av[ctr] != NULL; ctr += 1)
        check = (launcher(av[ctr], ac) ? 84 : check);
    return (check);
}