/*
** EPITECH PROJECT, 2019
** CPool_Day03_2019
** File description:
** void
*/

#include "my.h"

int my_put_nbr_ul(unsigned long long int nb)
{
    int i = 0;
    int len_wrote = 0;
    char c;

    while (nb / my_power_rec(10, i) >= 10) {
        i++;
    }
    len_wrote += i + 1;
    while (i >= 0) {
        c = ((nb / my_power_rec(10, i)) % 10) + '0';
        my_putchar(c);
        i--;
    }
    return len_wrote;
}

int my_put_nbr(long long int nb)
{
    int i = 0;
    int len_wrote = 0;
    char c;

    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
        len_wrote++;
    }
    while (nb / my_power_rec(10, i) >= 10) {
        i++;
    }
    len_wrote += (i + 1);
    while (i >= 0) {
        c = ((nb / my_power_rec(10, i)) % 10) + '0';
        my_putchar(c);
        i--;
    }
    return len_wrote;
}
