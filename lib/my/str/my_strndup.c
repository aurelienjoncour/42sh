/*
** EPITECH PROJECT, 2019
** LIBMY
** File description:
** 12/03/2020
*/

#include "my.h"

char *my_strndup(char const *src, int size)
{
    char *cpy = NULL;
    int length;

    if (!src)
        return NULL;
    length = my_strlen(src);
    if (length > size) {
        length = size;
    }
    cpy = malloc(sizeof(char) * (length + 1));
    if (cpy == NULL)
        return NULL;
    my_strncpy(cpy, src, length);
    cpy[length] = '\0';
    return cpy;
}
