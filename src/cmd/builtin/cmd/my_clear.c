/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** shell command function
*/

#include "shell.h"

int my_clear(char **cmd, shell_t *shell)
{
    (void)cmd;
    my_putstr("\e[1;1H\e[2J");
    shell->exit_status = SUCCESS_STATUS;
    return EXIT_SUCCESS;
}
