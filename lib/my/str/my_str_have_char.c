/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** Created: 2020-03-26T15:40:21+01:00 | Author: simon
*/

#include "my.h"

int my_str_have_char(const char *str, char c)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            return (int)i;
        }
    }
    return -1;
}
