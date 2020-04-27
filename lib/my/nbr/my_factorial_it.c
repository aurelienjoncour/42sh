/*
** EPITECH PROJECT, 2019
** CPool_Day05_2019
** File description:
** Task01
*/

#include <sys/types.h>

int my_factorial_it(const int nb)
{
    int result = 1;

    if (nb < 0 || nb > 12)
        return 0;
    for (ssize_t i = 1; i <= nb; i++) {
        result *= i;
    }
    return result;
}
