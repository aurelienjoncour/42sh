/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** Created: 2020-03-26T15:40:21+01:00 | Author: simon
*/

#include "my.h"

bool my_str_replace_char(char *str, const char *from, const char *to)
{
    bool have_change = false;
    int idx;

    for (size_t i = 0; str[i] != '\0'; i++) {
        idx = my_str_have_char(from, str[i]);
        if (idx != -1) {
            str[i] = to[idx];
            have_change = true;
        }
    }
    return have_change;
}
