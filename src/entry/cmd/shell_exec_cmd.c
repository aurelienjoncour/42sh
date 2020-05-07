/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** function
*/

#include "shell.h"

int minishell_exec_cmd(shell_t *shell, char **cmd)
{
    int ret = minishell_exec_shell_cmd(cmd, shell);

    if (ret == EXIT_FAIL) {
        ret = minishell_exec_bin_cmd(cmd, shell);
    }
    if (ret == EXIT_FAIL && cmd) {
        my_putstr_error(cmd[0]);
        my_putstr_error(": Command not found.\n");
        shell->exit_status = ERROR_STATUS;
    }
    return EXIT_SUCCESS;
}
