/*
** EPITECH PROJECT, 2019
** 42
** File description:
** 42
*/

#include <stdbool.h>
#include <stddef.h>

void rm_char(char *line, size_t *pos, bool stat)
{
    size_t i = 0;

    if (stat)
        i = *pos;
    else if (*pos > 0) {
        i = *pos - 1;
        if (*pos != 0)
            *pos -= 1;
    }
    else
        return;
    for (; line[i]; i++)
        line[i] = line[i + 1];
    line[i] = '\0';
}