/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-08T15:31:40+02:00 | Author: simon
*/

#include "shell.h"

static token_t *get_next_separator(token_t *ptr)
{
    if (ptr == NULL) {
        return NULL;
    }
    for (; ptr != NULL; ptr = ptr->next) {
        if (ptr->id == ID_OR || ptr->id == ID_AND) {
            return ptr;
        }
    }
    return NULL;
}

static bool check_break_loop(token_t *ptr, shell_t *shell)
{
    if (ptr != NULL && ptr->id == ID_OR) {
        if (shell->exit_status != 0) {
            return false;
        }
    } else if (ptr != NULL && ptr->id == ID_AND) {
        if (shell->exit_status == 0) {
            return false;
        }
    }
    return true;
}

int shell_exec_boolop(shell_t *shell, cmd_t *pipe_cmd)
{
    cmd_t **bool_cmd = split_cmd_list(pipe_cmd, ID_OR, ID_AND);
    token_t *ptr = pipe_cmd->begin;

    for (size_t i = 0; bool_cmd[i] != NULL; i++) {
        // TO DO : call script layer
        // <==
        ptr = get_next_separator(ptr);
        if (check_break_loop(ptr, shell)) {
            break;
        }
    }
    cmd_array_destroy(bool_cmd);
    return EXIT_SUCCESS;
}
