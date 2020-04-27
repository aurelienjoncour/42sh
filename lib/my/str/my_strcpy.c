/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** Task01
*/

#include "my.h"

char *my_strcpy(char *dest, char const *src)
{
    int size = my_strlen(src);

    return (my_strncpy(dest, src, size));
}
