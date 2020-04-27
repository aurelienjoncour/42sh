/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** Task05
*/

#include "my.h"

char *my_strstr(char *str, char const *to_find)
{
    int len_fd = my_strlen(to_find);

    if (!to_find || !str || to_find[0] == '\0')
        return str;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == to_find[0] && my_strncmp(&str[i], to_find, len_fd) == 0)
            return (&str[i]);
    }
    return NULL;
}
