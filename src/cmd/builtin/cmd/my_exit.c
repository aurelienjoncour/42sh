/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** shell command function
*/

#include "shell.h"

static const char *ERR_SYNT = "exit: Expression Syntax.\n";
static const char *ERR_NBR = "exit: Badly formed number.\n";

static bool char_is_number(char c, size_t pos)
{
    if (c == '-' && pos == 0) {
        return true;
    } else if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

static int check_exit_status(char *status)
{
    bool is_number = false;
    bool eval;

    if (my_strcmp(status, "-") == 0) {
        return -1;
    }
    for (size_t i = 0; status[i] != '\0'; i++) {
        eval = char_is_number(status[i], i);
        if (is_number == false && eval == false) {
            return -1;
        } else if (eval == false) {
            return -2;
        } else {
            is_number = true;
        }
    }
    return 0;
}

int my_exit(char **cmd, shell_t *shell)
{
    int ret;

    if (cmd[1] != NULL && cmd[1][0] != '\0') {
        ret = check_exit_status(cmd[1]);
        if (ret == -1 || cmd[2] != NULL) {
            my_putstr(ERR_SYNT);
            shell->exit_status = ERROR_STATUS;
            return EXIT_ERROR;
        } else if (ret == -2) {
            my_putstr(ERR_NBR);
            shell->exit_status = ERROR_STATUS;
            return EXIT_ERROR;
        }
        shell->exit_status = (char)my_getnbr(cmd[1]);
    }
    shell->exit = 1;
    if (isatty(0)) {
        write_history(&shell->history);
        my_putstr_error("exit\n");
    }
    return EXIT_SUCCESS;
}
