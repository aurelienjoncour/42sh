/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** Task02
*/

#include <stddef.h>

char *my_strncpy(char *dest, char const *src, int n)
{
    int n_greater_than_src = 0;

    if (n <= 0)
        return dest;
    for (size_t i = 0; i < (size_t)n; i++) {
        if (src[i] == '\0') {
            n_greater_than_src = 1;
            dest[i] = '\0';
            break;
        }
        dest[i] = src[i];
    }
    if (!n_greater_than_src)
        dest[n] = '\0';
    return dest;
}
