/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-11T13:19:19+02:00 | Author: simon
*/

#include "shell.h"

static int call_check_function(cmd_t *cmd, const char *entry)
{
    if (have_missing_str_quote(entry) == true) {
        return EXIT_ERROR;
    } else if (have_missing_name_redirection(cmd) == true) {
        return EXIT_ERROR;
    }
    if (check_position_redirection_in_pipe(cmd) == true) {
        return EXIT_ERROR;
    }
    if (have_several_redirection(cmd) == true) {
        return EXIT_ERROR;
    } else if (have_null_command(cmd) == true) {
        return EXIT_ERROR;
    }
    if (check_have_empty_pipe(cmd) == true) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

int entry_checker(shell_t *shell, cmd_t *cmd, const char *entry)
{
    if (call_check_function(cmd, entry) == EXIT_ERROR) {
        shell->exit_status = ERROR_STATUS;
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
