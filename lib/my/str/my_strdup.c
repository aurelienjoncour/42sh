/*
** EPITECH PROJECT, 2019
** CPool_Day08_2019
** File description:
** Task01
*/

#include "my.h"

char *my_strdup(char const *src)
{
    char *cpy = NULL;
    int len_src;

    if (!src)
        return NULL;
    len_src = my_strlen(src);
    cpy = malloc(sizeof(char) * (len_src + 1));
    if (cpy == NULL)
        return NULL;
    my_strcpy(cpy, src);
    cpy[len_src] = '\0';
    return cpy;
}
