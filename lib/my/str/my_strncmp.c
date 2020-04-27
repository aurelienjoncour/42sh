/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** Task07
*/

#include "my.h"

int my_strncmp(char const *s1, char const *s2, int n)
{
    for (size_t i = 0; i < (size_t)n; i++) {
        if ((s1[i] - s2[i]) != 0) {
            return (s1[i] - s2[i]);
        }
        if (s1[i] == '\0' || s2[i] == '\0')
            break;
    }
    return 0;
}
