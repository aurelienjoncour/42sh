/*
** EPITECH PROJECT, 2019
** CPool_Day05_2019
** File description:
** Task05
*/

#include <stddef.h>

int my_compute_square_root(const int nb)
{
    size_t result = 1;

    if (nb <= 0)
        return 0;
    while ((result * result) < (size_t)nb && result <= 46340) {
        result++;
    }
    if ((result * result) != (size_t)nb)
        return 0;
    return result;
}
