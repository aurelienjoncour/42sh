/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** Task03
*/

#include "my.h"

char *my_revstr(char *str)
{
    char temp;
    size_t len = my_strlen(str);

    for (size_t i = (len - 1); i > (len / 2); i--) {
        temp = str[len - i];
        str[len - i] = str[i];
        str[i] = temp;
    }
    return str;
}
