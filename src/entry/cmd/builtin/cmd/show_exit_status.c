/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** Created: 2020-04-16T15:15:29+02:00 | Author: simon
*/

#include "shell.h"

int show_exit_status(char **cmd, shell_t *shell)
{
    (void)cmd;
    my_printf("Exit status: %d\n", shell->exit_status);
    return EXIT_SUCCESS;
}
