/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 43sh
*/

#include "shell.h"

char *space_cat(char *str, char *src)
{
    size_t size = (str) ? strlen(str) + strlen(src) : strlen(src);
    char *new = malloc(sizeof(char) * (size + 1));
    size_t move = 0;

    if (!new)
        return NULL;
    if (str) {
        for (size_t i = 0; str[i]; i++)
            new[move++] = str[i];
        free(str);
    }
    for (size_t i = 0; src[i]; i++)
        if (src[i] == '\n')
            src[i] = ' ';
    for (size_t i = 0; src[i]; i++)
        new[move++] = src[i];
    new[move] = '\0';
    return new;
}
