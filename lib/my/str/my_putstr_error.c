/*
** EPITECH PROJECT, 2019
** my_put_str_error
** File description:
** write a string on the error output
*/

#include "my.h"

int my_putstr_error(const char *str)
{
    int len;

    if (!str)
        return 0;
    len = my_strlen(str);
    write(2, str, len);
    return len;
}

int my_puterror(const char *str, int status)
{
    if (!str)
        return 0;
    write(2, str, my_strlen(str));
    return status;
}

int puterr(const char *str, int status)
{
    return my_puterror(str, status);
}
