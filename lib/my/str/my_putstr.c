/*
** EPITECH PROJECT, 2019
** CPool_Day04_2019
** File description:
** Task02
*/

#include "my.h"

int my_putstr(char const *str)
{
    int len;

    if (!str)
        return 0;
    len = my_strlen(str);
    write(1, str, len);
    return len;
}
