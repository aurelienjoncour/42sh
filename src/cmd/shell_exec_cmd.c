/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** function
*/

#include "shell.h"

int shell_exec_cmd(shell_t *shell, char **cmd)
{
    int ret = shell_exec_shell_cmd(cmd, shell);

    if (ret == EXIT_FAIL) {
        ret = shell_exec_bin_cmd(cmd, shell);
    }
    if (ret == EXIT_FAIL && cmd) {
        fprintf(stderr, "%s: Command not found.\n", cmd[0]);
        shell->exit_status = ERROR_STATUS;
    }
    return EXIT_SUCCESS;
}
