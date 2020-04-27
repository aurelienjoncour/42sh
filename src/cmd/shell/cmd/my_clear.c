/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** shell command function
*/

#include "minishell.h"

int my_clear(char **cmd, minishell_t *shell)
{
    (void)cmd;
    (void)shell;
    my_putstr("\e[1;1H\e[2J");
    shell->exit_status = SUCCESS_STATUS;
    return EXIT_SUCCESS;
}
