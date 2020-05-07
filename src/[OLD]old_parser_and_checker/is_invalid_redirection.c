/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-13T11:41:48+02:00 | Author: simon
*/

#include "shell.h"

bool is_invalid_redirection(const char *str)
{
    int serie[2];
    int occur[2];

    my_str_count_char_suite(str, '<', &occur[0], &serie[0]);
    my_str_count_char_suite(str, '>', &occur[1], &serie[1]);
    if (occur[0] == 0 && occur[1] == 0) {
        return false;
    } else if (occur[0] > 0 && occur[1] > 0) {
        return true;
    }
    if (occur[0] > 2 || occur[1] > 2) {
        return true;
    }
    return false;
}
