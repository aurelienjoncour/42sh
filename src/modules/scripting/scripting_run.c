/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-08T15:35:23+02:00 | Author: simon
*/

#include "shell.h"

static void remove_comment(char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '#') {
            str[i] = '\0';
            break;
        }
    }
}

static bool is_empty(char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\t') {
            return false;
        }
    }
    return true;
}

int shell_scripting_run(shell_t *shell)
{
    char **content = my_read_file(shell->shell_script);
    bool str_is_empty;

    if (!content) {
        return ERROR_STATUS;
    }
    for (size_t i = 0; content[i] != NULL && !shell->exit; i++) {
        remove_comment(content[i]);
        str_is_empty = is_empty(content[i]);
        if (str_is_empty == false
            && shell_exec(shell, content[i]) == EXIT_ERROR) {
            break;
        } else if (str_is_empty == true) {
            free(content[i]);
        }
    }
    free(content);
    return shell->exit_status;
}
