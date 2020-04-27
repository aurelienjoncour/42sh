/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** Task20
*/

#include "my.h"

int my_showstr(char const *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] < 32 || str[i] > 126) {
            my_putchar('\\');
            my_putnbr_base(str[i], "0123456789abcdef");
        } else {
            my_putchar(str[i]);
        }
    }
    return EXIT_SUCCESS;
}
