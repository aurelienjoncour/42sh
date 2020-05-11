/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** shell command function
*/

#include "shell.h"

int my_env(char **cmd, shell_t *shell)
{
    int len = word_array_len(cmd);

    if (len == 1) {
        my_env_display(&shell->env);
    }
    shell->exit_status = SUCCESS_STATUS;
    return EXIT_SUCCESS;
}
