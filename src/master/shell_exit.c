/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** minishell main function
*/

#include "minishell.h"

void minishell_exit(minishell_t *shell, int status)
{
    shell->exit_status = status;
    shell->exit = true;
}
