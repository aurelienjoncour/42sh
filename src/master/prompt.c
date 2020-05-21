/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** function
*/

#include "shell.h"

static void show_user(char *user, char *host)
{
    if (host) {
        fprintf(stdout, "%s", "\033[4m");
        fprintf(stdout, "%s", host);
        fprintf(stdout, "%s", "\033[0m\033[31m");
    } else if (user) {
        fprintf(stdout, "%s", "\033[4m");
        fprintf(stdout, "%s", user);
        fprintf(stdout, "%s", "\033[0m\033[31m");
    }
}

void show_main_prompt(shell_t *shell)
{
    char *host = my_env_get_value(&shell->env, "HOST");
    char *user = my_env_get_value(&shell->env, "USER");
    char *path = getcwd(NULL, 0);

    fprintf(stdout, "%s", "\033[31m");
    show_user(user, host);
    my_putchar(':');
    fprintf(stdout, "%s", "\033[1m");
    display_path_without_homepath(&shell->env, path);
    fprintf(stdout, "%s", "\033[0m\033[31m");
    fprintf(stdout, " % 3i%s", shell->exit_status, "> \033[0m");
    free(path);
    free(host);
    free(user);
}