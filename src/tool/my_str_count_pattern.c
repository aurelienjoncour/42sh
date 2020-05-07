/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-08T09:28:21+02:00 | Author: simon
*/

#include "my.h"

int my_str_count_pattern(char *str, const char *pattern)
{
    int len_pattern = my_strlen(pattern);
    int count = 0;
    char *ptr = str;

    do {
        ptr = my_strstr(ptr, pattern);
        if (ptr != NULL) {
            count++;
            ptr += len_pattern;
        }
    } while (ptr != NULL);
    return count;
}
