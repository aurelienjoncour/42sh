/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-18T10:21:27+02:00 | Author: simon
*/

#include "shell.h"

int substr_variables(shell_t *shell, cmd_t *cmd)
{
    token_t *curr_token;

    for (token_t *ptr = cmd->begin; ptr != NULL;) {
        if (try_subst_variable(ptr, shell) == EXIT_ERROR) {
            return EXIT_FAIL;
        }
        if (is_command_name(ptr) == true) {
            curr_token = ptr;
            ptr = ptr->next;
            if (try_subst_alias(cmd, curr_token, shell) == EXIT_ERROR) {
                return EXIT_ERROR;
            }
        } else {
            ptr = ptr->next;
        }
    }
    return EXIT_SUCCESS;
}
