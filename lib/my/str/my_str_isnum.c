/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** Task13
*/

#include <stdbool.h>
#include <stddef.h>

bool my_str_isnum(char const *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if ((str[i] < '0' || str[i] > '9') && !(i == 0 && str[0] == '-'))
            return false;
    }
    return true;
}
