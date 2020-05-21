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

int my_strcmp_nocase(char const *s1, char const *s2)
{
    int len_s1 = my_strlen(s1);
    int len_s2 = my_strlen(s2);
    char *s1_low = my_strdup(s1);
    char *s2_low = my_strdup(s2);
    int size;
    int ret;

    if (!s1_low || !s2_low)
        return 0;
    s1_low = my_strlowcase(s1_low);
    s2_low = my_strlowcase(s2_low);
    if (len_s1 > len_s2)
        size = len_s1;
    else
        size = len_s2;
    ret = my_strncmp(s1_low, s2_low, size);
    free(s1_low);
    free(s2_low);
    return ret;
}
