/*
** EPITECH PROJECT, 2019
** CPool_Day07_2019
** File description:
** Task02
*/

#include "my.h"

char *my_strcat(char *dest, const char *src)
{
    int len_dest = my_strlen(dest);
    int i = len_dest;

    for (size_t j = 0; src[j] != '\0'; j++) {
        dest[i] = src[j];
        i++;
    }
    return dest;
}
