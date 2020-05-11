/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** minishell main function
*/

#include "shell.h"

int shell_create(shell_t *shell, char **env)
{
    if (my_env_create(&shell->env, env) != EXIT_SUCCESS) {
        return EXIT_ERROR;
    }
    if (my_env_create(&shell->local, env) != EXIT_SUCCESS) {
        return EXIT_ERROR;
    }
    shell->prev_path = NULL;
    shell->exit = false;
    shell->exit_status = EXIT_SUCCESS;
    shell->fd.stdin = dup(0);
    shell->fd.stdout = dup(1);
    shell->fd.prev_pipein = -1;
    if (shell->fd.stdin == -1 || shell->fd.stdout == -1) {
        return puterr("dup : fail\n", EXIT_ERROR);
    }
    return EXIT_SUCCESS;
}

int shell_destroy(shell_t *shell)
{
    my_env_destroy(&shell->env);
    my_env_destroy(&shell->local);
    free(shell->prev_path);
    close(shell->fd.stdin);
    close(shell->fd.stdout);
    return EXIT_SUCCESS;
}
