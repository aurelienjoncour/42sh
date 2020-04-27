/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** Task16
*/

#include <stdbool.h>
#include <stddef.h>

bool my_str_isprintable(char const *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] < 32 || str[i] > 126)
            return false;
    }
    return true;
}
