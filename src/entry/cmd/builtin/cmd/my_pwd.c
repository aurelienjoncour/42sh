/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** shell command function
*/

#include "shell.h"

int my_pwd(char **cmd, shell_t *shell)
{
    char *pwd = NULL;

    (void)cmd;
    (void)shell;
    pwd = getcwd(NULL, 0);
    if (pwd)
        my_putstr(pwd);
    my_putchar('\n');
    free(pwd);
    shell->exit_status = SUCCESS_STATUS;
    return EXIT_SUCCESS;
}
