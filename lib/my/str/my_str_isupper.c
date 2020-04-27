/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** task15
*/

#include "my.h"

bool my_str_isupper(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] > 'Z' || str[i] < 'A')
            return false;
    }
    return true;
}
