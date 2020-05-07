/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** main function
*/

#include "shell.h"

int main(int argc, char **argv, char **env)
{
    shell_t minishell;
    int ret;

    (void)argc;
    (void)argv;
    if (minishell_create(&minishell, env)) {
        return EXIT_ERROR;
    } else {
        ret = minishell_run(&minishell);
        minishell_destroy(&minishell);
        return ret;
    }
}
