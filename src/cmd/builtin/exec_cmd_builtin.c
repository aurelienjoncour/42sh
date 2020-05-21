/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** function
*/

#include "shell.h"

const char *BUILTIN_NAME[] =
{
    "cd",
    "exit",
    "env",
    "setenv",
    "unsetenv",
    "clear",
    "my_pwd",
    "??",
    "echo",
    "alias",
    "unalias",
    "set",
    "which",
    "where",
    "history",
    "fg",
    "repeat",
    NULL
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
    &show_exit_status,
    &my_echo,
    &my_alias,
    &my_unalias,
    &my_set,
    &my_which,
    &my_where,
    &built_in_history,
    NULL,
    &my_repeat
};

int shell_exec_shell_cmd(char **cmd, shell_t *shell)
{
    int idx_cmd = word_array_search2(BUILTIN_NAME, cmd[0]);
    int ret;

    if (idx_cmd == -1) {
        return EXIT_FAIL;
    } else if (CMD_FUNCT_PTR[idx_cmd] != NULL) {
        ret = CMD_FUNCT_PTR[idx_cmd](cmd, shell);
        if (ret == EXIT_ERROR)
            return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
