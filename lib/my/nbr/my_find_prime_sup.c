/*
** EPITECH PROJECT, 2019
** CPool_Day05_2019
** File description:
** Task07
*/

#include "my.h"

int my_find_prime_sup(const int nb)
{
    size_t pr = nb;

    while (my_is_prime(pr) == 0) {
        if (pr == 2147483647)
            return nb;
        pr++;
    }
    return pr;
}
