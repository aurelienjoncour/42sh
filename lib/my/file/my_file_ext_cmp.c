/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** Created: 2020-03-26T19:46:58+01:00 | Author: simon
*/

#include "my.h"

bool my_file_ext_cmp(const char *filepath, const char *extension)
{
    int dot_position = -1;

    for (int i = 0; filepath[i] != '\0'; i++) {
        if (filepath[i] == '.')
            dot_position = i;
    }
    if (dot_position == -1) {
        return false;
    } else if (my_strcmp(&filepath[dot_position], extension) == 0) {
        return true;
    }
    return false;
}
