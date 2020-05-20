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
    ptr = ptr->next;
    while (ptr != NULL) {
        if (ptr->id == ID_OR || ptr->id == ID_AND) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

static int check_break_loop(token_t *ptr, shell_t *shell)
{
    int ret = 0;

    if (ptr != NULL && ptr->id == ID_OR) {
        if (shell->exit_status == 0) {
            return -1;
        }
    } else if (ptr != NULL && ptr->id == ID_AND) {
        if (shell->exit_status == 0) {
            return 0;
        }
        while (ptr != NULL && ptr->id != ID_OR) {
            ret++;
            ptr = get_next_separator(ptr);
        }
        return ret;
    }
    return 0;
}

int shell_exec_boolop(shell_t *shell, cmd_t *pipe_cmd)
{
    cmd_t **bool_cmd = split_cmd_list(pipe_cmd, ID_OR, ID_AND);
    token_t *ptr = pipe_cmd->begin;
    int ret;

    for (size_t i = 0; bool_cmd[i] != NULL; i++) {
        if (bool_cmd[i]->begin == NULL)
            continue;
        if (shell_exec_script(shell, bool_cmd[i]) == EXIT_ERROR) {
            return EXIT_ERROR;
        }
        ptr = get_next_separator(ptr);
        ret = check_break_loop(ptr, shell);
        if (ret > 0 && bool_cmd[i + ret] != NULL) {
            i += ret;
        } else if (ret == -1) {
            break;
        }
    }
    cmd_array_destroy(bool_cmd);
    return EXIT_SUCCESS;
}
