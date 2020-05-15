/*
** EPITECH PROJECT, 2019
** 42
** File description:
** 42
*/

#include <stdlib.h>
#include "my.h"

static char *malloc_size(char *str)
{
    char *ret;

    if (str)
        ret = malloc(sizeof(char) * (my_strlen(str) + 3));
    else
        ret = malloc(sizeof(char) * 2);
    return ret;
}

char *add_char(char *str, char c, size_t pos)
{
    char *ret;
    size_t i = 0;
    size_t move = 0;

    ret = malloc_size(str);
    if (!ret)
        return NULL;
    for (i = 0; str && str[move] != '\0'; i++)
        if (i == pos)
            ret[i] = c;
        else {
            ret[i] = str[move];
            move++;
        }
    if (!str || pos == i)
        ret[i++] = c;
    ret[i] = '\0';
    if (str)
        free(str);
    return ret;
}