/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-11T13:19:19+02:00 | Author: simon
*/

#include "shell.h"

int entry_checker(shell_t *shell, cmd_t *cmd, const char *entry)
{
    if (check_have_empty_pipe(cmd)) {
        shell->exit_status = ERROR_STATUS;
    }
    if (check_position_redirection_in_pipe(cmd)) {
        shell->exit_status = ERROR_STATUS;
    }
    return EXIT_SUCCESS;
}
