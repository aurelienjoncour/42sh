/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-08T15:35:23+02:00 | Author: simon
*/

#include "shell.h"

int shell_exec_script(shell_t *shell, cmd_t *boolop_cmd)
{
    if (eval_if_condition(boolop_cmd) == EXIT_ERROR) {
        shell->exit_status = ERROR_STATUS;
        return EXIT_SUCCESS;
    }
    // TODO : while + foreach eval

    if (cmd_process(shell, boolop_cmd) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
