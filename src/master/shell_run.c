/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** minishell main function
*/

#include "shell.h"

static bool handle_end_of_file(shell_t *shell, int *end_of_file)
{
    int ignoreeof_val = 0;
    char *ignoreeof_str_val = NULL;

    *end_of_file += 1;
    if (my_env_exist(&shell->local, "ignoreeof")) {
        ignoreeof_str_val = get_env_entry(&shell->local, "ignoreeof=");
        if (my_strcmp(ignoreeof_str_val, "") == 0) {
            shell->exit = true;
            return true;
        }
        ignoreeof_val = my_getnbr(ignoreeof_str_val);
        if (ignoreeof_val == 0 || ignoreeof_val != *end_of_file) {
            printf("\nUse \"exit\" to leave 42sh.\n");
            return false;
        } else {
            shell->exit = true;
            return true;
        }
    }
    return true;
}

int shell_run(shell_t *shell)
{
    char *entry = NULL;
    static int end_of_file = 0;

    if (shell->shell_script != NULL)
        return shell_scripting_run(shell);
    while (!shell->exit) {
        entry = terminal_read(shell);
        if (!entry && handle_end_of_file(shell, &end_of_file))
            break;
        else if (!entry)
            continue;
        end_of_file = 0;
        if (!(entry != NULL && entry[0] == '\0'))
            if (shell_exec(shell, entry) != EXIT_SUCCESS)
                return EXIT_ERROR;
        if (my_env_exist(&shell->alias, "precmd") && shell_exec(shell,
        get_env_entry(&shell->alias, "precmd=")) != EXIT_SUCCESS)
                return EXIT_ERROR;
    }
    return shell->exit_status;
}
