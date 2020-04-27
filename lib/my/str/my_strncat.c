/*
** EPITECH PROJECT, 2019
** CPool_Day07_2019
** File description:
** Task03
*/

#include "my.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    int len_dest = my_strlen(dest);
    int i = len_dest;

    for (size_t j = 0; (src[j] != '\0') && (j < (size_t)nb); j++) {
        dest[i] = src[j];
        i++;
    }
    return dest;
}
