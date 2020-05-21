/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** minishell main function
*/

#include "shell.h"

static void init_struct(shell_t *shell, char *shell_script)
{
    shell->prev_path = NULL;
    shell->exit = false;
    shell->exit_status = EXIT_SUCCESS;
    shell->fd.stdin = dup(0);
    shell->fd.stdout = dup(1);
    shell->fd.prev_pipein = -1;
    shell->shell_script = shell_script;
}

int shell_create(shell_t *shell, char **env, char *shell_script)
{
    char **default_local = get_default_local(env);

    if (my_env_create(&shell->env, env) != EXIT_SUCCESS)
        return EXIT_ERROR;
    if (my_env_create(&shell->local, default_local) != EXIT_SUCCESS)
        return EXIT_ERROR;
    if (my_env_create(&shell->alias, NULL) != EXIT_SUCCESS)
        return EXIT_ERROR;
    init_struct(shell, shell_script);
    if ((!init_history(&shell->history) || !init_input())) {
        return EXIT_ERROR;
    }
    if (shell->fd.stdin == -1 || shell->fd.stdout == -1)
        return puterr("dup : fail\n", EXIT_ERROR);
    signal(SIGINT, handler);
    for (size_t i = 0; default_local[i]; i++)
        free(default_local[i]);
    free(default_local);
    return EXIT_SUCCESS;
}

int shell_destroy(shell_t *shell)
{
    destroy_history(&shell->history);
    my_env_destroy(&shell->env);
    my_env_destroy(&shell->local);
    my_env_destroy(&shell->alias);
    free(shell->prev_path);
    close(shell->fd.stdin);
    close(shell->fd.stdout);
    return EXIT_SUCCESS;
}
