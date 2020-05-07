/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** Created: 2020-04-15T17:49:09+02:00 | Author: simon
*/

#include "shell.h"

bool check_sub_entry(const char *sub_entry)
{
    if (check_position_redirection_in_pipe(sub_entry)) {
        return true;
    }
    return false;
}
