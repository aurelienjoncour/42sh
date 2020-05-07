/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** tool function
*/

#include "shell.h"

// Replace HOME PATH => '~'

void display_path_without_homepath(env_t *env, char *path)
{
    char *home_path = my_env_get_value(env, "HOME");

    if (!path) {
        my_putstr_error("Error: display_path_hide_homepath - null path\n");
    }
    if (!home_path) {
        my_putstr(path);
        free(home_path);
        return;
    } else if (my_strstr(path, home_path) != &path[0]) {
        my_putstr(path);
        free(home_path);
        return;
    }
    my_putchar('~');
    my_putstr(path + my_strlen(home_path));
    free(home_path);
}
