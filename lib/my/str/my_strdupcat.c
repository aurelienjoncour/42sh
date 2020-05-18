/*
** EPITECH PROJECT, 2019
** my_strdup
** File description:
** allocate memory and copy multiple strings
*/

#include <stdlib.h>
#include <stdarg.h>
#include "my.h"

static int get_len(int argc, va_list vl)
{
    int len = 0;
    va_list vl_count;

    va_copy(vl_count, vl);
    for (int i = 0; i < argc; i++)
        len += my_strlen(va_arg(vl_count, char *));
    va_end(vl_count);
    return len;
}

char *my_strdupcat(int argc, ...)
{
    char *dest;
    va_list vl;
    int k = 0;
    char *str;

    if (argc <= 0)
        return NULL;
    va_start(vl, argc);
    dest = malloc(sizeof(char) * (get_len(argc, vl) + 1));
    if (dest == NULL)
        return NULL;
    for (int i = 0; i < argc; i++) {
        str = va_arg(vl, char *);
        for (int x = 0; str != NULL && str[x] != '\0'; x++, k++)
            dest[k] = str[x];
    }
    dest[k] = '\0';
    va_end(vl);
    return dest;
}