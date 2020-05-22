/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-22T11:51:56+02:00 | Author: simon
*/

#include "shell.h"

int load_argv(shell_t *shell, char **argv)
{
    char buffer[1024];

    for (size_t i = 0; argv[i] != NULL; i++) {
        sprintf(buffer, "%lu", i);
        if (my_env_add(&shell->local, buffer, argv[i]) == EXIT_ERROR) {
            return EXIT_ERROR;
        }
    }
    return EXIT_SUCCESS;
}
