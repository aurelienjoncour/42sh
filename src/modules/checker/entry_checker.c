/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-11T13:19:19+02:00 | Author: simon
*/

#include "shell.h"

static const char *ERR_PIPE_NULL_CMD = "Invalid null command.\n";

static bool check_have_empty_pipe(cmd_t *cmd)
{
    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (ptr->id == ID_PIPE && (!ptr->next
                || (ptr->next->type == D_SEPARATOR
                    || ptr->next->id == ID_PIPE)) {
            my_putstr(ERR_NULL_CMD);
            return true;
        }
    }
    return false;
}

int entry_checker(shell_t *shell, cmd_t *cmd)
{
    if (check_have_empty_pipe(cmd)) {
        shell->exit_status = ERROR_STATUS;
    }
    if (check_position_redirection_in_pipe(cmd)) {
        shell->exit_status = ERROR_STATUS;
    }
    return EXIT_SUCCESS;
}
