/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** minishell main function
*/

#include "shell.h"

void minishell_exit(shell_t *shell, int status)
{
    shell->exit_status = status;
    shell->exit = true;
}
