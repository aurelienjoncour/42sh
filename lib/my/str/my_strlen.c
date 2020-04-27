/*
** EPITECH PROJECT, 2019
** CPool_Day04_2019
** File description:
** Task03
*/

#include <stddef.h>

int my_strlen(char const *str)
{
    int len = 0;

    if (!str)
        return 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        len++;
    }
    return len;
}
