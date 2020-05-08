/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** minishell main function
*/

#include "shell.h"

int shell_run(shell_t *shell)
{
    char *entry = NULL;

    while (!shell->exit) {
        entry = shell_prompt(shell);
        if (!entry || (entry != NULL && entry[0] == '\0')) {
            shell->exit = true;
            break;
        }
        if (shell_exec(shell, entry) != EXIT_SUCCESS)
            return EXIT_ERROR;
    }
    return shell->exit_status;
}
