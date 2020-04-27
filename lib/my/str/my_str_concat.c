/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** Created: 2020-03-25T17:56:35+01:00 | Author: simon
*/

#include "my.h"

char *my_str_concat(const char *stra, const char *strb)
{
    int len = 0;
    int len_stra = my_strlen(stra);
    char *result = NULL;

    len = len_stra + my_strlen(strb);
    if (len == 0)
        return NULL;
    result = malloc(sizeof(char) * (len + 1));
    if (!result)
        return NULL;
    if (stra) {
        my_strcpy(result, stra);
    }
    if (strb) {
        my_strcpy(result + len_stra, strb);
    }
    result[len] = '\0';
    return result;
}
