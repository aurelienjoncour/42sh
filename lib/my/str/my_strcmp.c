/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** Task06
*/

#include "my.h"

int my_strcmp(char const *s1, char const *s2)
{
    int len_s1 = my_strlen(s1);
    int len_s2 = my_strlen(s2);
    int size;

    if (len_s1 > len_s2)
        size = len_s1;
    else
        size = len_s2;
    return (my_strncmp(s1, s2, size));
}
