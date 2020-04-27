/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** Task09
*/

#include "my.h"

char *my_strlowcase(char *str)
{
    if (!str)
        return NULL;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] <= 'Z' && str[i] >= 'A')
            str[i] -= ('A' - 'a');
    }
    return str;
}
