/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** minishell main function
*/

#include "shell.h"

int minishell_run(shell_t *shell)
{
    char *entry = NULL;

    while (!shell->exit) {
        entry = minishell_prompt(shell);
        if (!entry || (entry != NULL && entry[0] == '\0')) {
            shell->exit = true;
            break;
        }
        if (minishell_exec(shell, entry) != EXIT_SUCCESS)
            return EXIT_ERROR;
    }
    return shell->exit_status;
}
