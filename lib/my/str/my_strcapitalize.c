/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** Task10
*/

/*
    type [l] : lower
    type [u] : upper
    type [a] : all
*/

#include "my.h"

static bool is_of_type(const char c, const char type)
{
    if (type == 'l' && c >= 'a' && c <= 'z')
        return true;
    if (type == 'u' && c >= 'A' && c <= 'Z')
        return true;
    if (type == 'a' && ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
        return true;
    if (type == 'a' && c >= '0' && c <= '9')
        return true;
    return false;
}

char *my_strcapitalize(char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (is_of_type(str[i], 'l') && (!i || !is_of_type(str[i - 1], 'a'))) {
            str[i] -= 32;
        }
        if (i > 0 && is_of_type(str[i], 'u') && is_of_type(str[i - 1], 'a')) {
            str[i] += 32;
        }
    }
    return str;
}
