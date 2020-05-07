/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** function
*/

#include "shell.h"

static const int NB_SHELL_CMD = 8;

static const char *CMD_NAME[] =
{
    "cd",
    "exit",
    "env",
    "setenv",
    "unsetenv",
    "clear",
    "my_pwd",
    "$?"
};

static int (* const CMD_FUNCT_PTR[])(char **cmd, shell_t *shell) =
{
    &my_cd,
    &my_exit,
    &my_env,
    &my_setenv,
    &my_unsetenv,
    &my_clear,
    &my_pwd,
    &show_exit_status
};

int minishell_exec_shell_cmd(char **cmd, shell_t *shell)
{
    int idx_cmd = word_array_search2(CMD_NAME, NB_SHELL_CMD, cmd[0]);
    int ret;

    if (idx_cmd == -1) {
        return EXIT_FAIL;
    } else {
        ret = CMD_FUNCT_PTR[idx_cmd](cmd, shell);
        if (ret == EXIT_ERROR)
            return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
