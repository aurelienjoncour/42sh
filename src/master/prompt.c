/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** function
*/

#include "minishell.h"

static void show_user(char *user, char *host)
{
    if (host) {
        my_putstr("\033[4m");
        my_putstr(host);
        my_putstr("\033[0m\033[31m");
    } else if (user) {
        my_putstr("\033[4m");
        my_putstr(user);
        my_putstr("\033[0m\033[31m");
    }
}

static void show_prompt(minishell_t *shell)
{
    char *host = my_env_get_value(&shell->env, "HOST");
    char *user = my_env_get_value(&shell->env, "USER");
    char *path = getcwd(NULL, 0);

    my_putstr("\033[31m");
    show_user(user, host);
    my_putchar(':');
    my_putstr("\033[1m");
    display_path_without_homepath(&shell->env, path);
    my_putstr("\033[0m\033[31m");
    my_putstr("> \033[0m");
    free(path);
    free(host);
    free(user);
}

char *minishell_prompt(minishell_t *shell)
{
    char *entry = NULL;
    size_t size = 0;
    int ret;

    do {
        free(entry);
        entry = NULL;
        if (isatty(0)) {
            show_prompt(shell);
        }
        ret = getline(&entry, &size, stdin);
    } while (entry && ret >= 1 && entry[0] == '\n');
    if (ret == -1) {
        free(entry);
        return NULL;
    }
    if (entry && entry[ret - 1] == '\n') {
        entry[ret - 1] = '\0';
    }
    return entry;
}
