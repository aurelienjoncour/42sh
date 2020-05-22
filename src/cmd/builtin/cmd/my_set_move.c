/*
** EPITECH PROJECT, 2019
** 55sh
** File description:
** 56sh
*/

#include "shell.h"

static char *get_this_line(char **cmd, size_t *i)
{
    char *ret;

    if (cmd[*i + 2]) {
        ret = my_strdupcat(3, cmd[*i], cmd[*i + 1], cmd[*i + 2]);
        *i += 2;
    }
    else {
        ret = my_strdupcat(2, cmd[*i], cmd[*i + 1]);
        *i += 1;
    }
    if (!ret)
        return NULL;
    return ret;
}

static int get_len(char **cmd)
{
    int pos = 0;

    for (size_t i = 1; cmd[i] != NULL; i++) {
        if (cmd[i + 1] && my_strcmp(cmd[i + 1], "=") == 0) {
            if (cmd[i + 2])
                i += 2;
            else
                i += 1;
        }
        pos++;
    }
    return pos + 1;
}

char **make_my_list(char **cmd)
{
    int len = get_len(cmd);
    char **tab = malloc(sizeof(char *) * len);
    size_t pos = 0;

    tab[0] = NULL;
    for (size_t i = 1; cmd[i] != NULL; i++) {
        if (cmd[i + 1] && my_strcmp(cmd[i + 1], "=") == 0) {
            tab[pos] = get_this_line(cmd, &i);
        }
        else {
            tab[pos] = my_strdup(cmd[i]);
        }
        tab[pos + 1] = NULL;
        if (!tab[pos])
            return NULL;
        pos++;
    }
    return tab;
}

int move_in_list(char **list, shell_t *shell, int *len)
{
    int ret;

    for (size_t i = 0; list[i] != NULL; i++) {
        if (str_have_only_chars(list[i], " \t") == true)
            continue;
        *len += 1;
        if (strcmp(list[i], "-r") == 0)
            continue;
        ret = set_variable_set(list, i, &shell->local);
        if (ret == EXIT_ERROR) {
            shell->exit_status = ERROR_STATUS;
            return EXIT_ERROR;
        }
    }
    return EXIT_SUCCESS;
}