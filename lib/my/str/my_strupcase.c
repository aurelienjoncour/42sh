/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** Task08
*/

#include <stddef.h>

char *my_strupcase(char *str)
{
    int delta = ('A' - 'a');

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] <= 'z' && str[i] >= 'a')
            str[i] += delta;
    }
    return str;
}
