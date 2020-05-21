/*
** EPITECH PROJECT, 2019
** 50sh
** File description:
** 51sh
*/

#include "shell.h"

int my_unset(char **cmd, shell_t *shell)
{
    int len = word_array_len(cmd);
    
    if (len <= 1) {
        fprintf(stderr, "%s\n", "unset: Too few arguments.");
        shell->exit_status = ERROR_STATUS;
        return ERROR_STATUS;
    }
    for (size_t i = 1; cmd[i]; i++) {
        my_env_rm(&shell->local, cmd[i]);
    }
    shell->exit_status = SUCCESS_STATUS;
    return SUCCESS_STATUS;
}