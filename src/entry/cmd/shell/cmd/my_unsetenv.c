/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** shell command function
*/

#include "shell.h"

int my_unsetenv(char **cmd, shell_t *shell)
{
    if (cmd[1] == NULL) {
        my_putstr_error("unsetenv: Too few arguments.\n");
        shell->exit_status = ERROR_STATUS;
        return EXIT_ERROR;
    }
    for (int i = 1; cmd[i] != NULL; i++) {
        my_env_rm(&shell->env, cmd[i]);
    }
    shell->exit_status = SUCCESS_STATUS;
    return EXIT_SUCCESS;
}
