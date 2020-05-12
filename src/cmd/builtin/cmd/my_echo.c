/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-11T14:15:56+02:00 | Author: simon
*/

#include "shell.h"

static const char *OPT_NO_NEW_LINE = "-n";

static bool is_option(const char *str)
{
    if (strlen(str) < 2 || strncmp(str, OPT_NO_NEW_LINE, 2) != 0) {
        return false;
    }
    for (size_t i = 2; str[i] != '\0'; i++) {
        if (str[i] != OPT_NO_NEW_LINE[1]) {
            return false;
        }
    }
    return true;
}

int my_echo(char **cmd, shell_t *shell)
{
    bool display_new_line = true;

    for (size_t i = 1; cmd[i] != NULL; i++) {
        if (is_option(cmd[i]) == true) {
            display_new_line = false;
        } else {
            printf("%s", cmd[i]);
        }
    }
    fflush(stdout);
    if (display_new_line == true) {
        printf("\n");
    }
    return EXIT_SUCCESS;
}
