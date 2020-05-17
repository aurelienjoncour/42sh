/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42
*/

#include "shell.h"


static bool is_flag(char c, hist_build_t *load)
{
    char flag[] = "crhsL";

    for (size_t i = 0; flag[i]; i++)
        if (flag[i] == c) {
            load->flag[i] = true;
            return true;
        }
    fprintf(stderr, "%s\n", USAGE_HISTORY);
    return false;
}

static bool param_manage(char **cmd, hist_build_t *ld, size_t i)
{
    if (my_str_isnum(cmd[i]) != 1 && !ld->flag[FLAG_S] && !ld->flag[FLAG_L]) {
        fprintf(stderr, "%s\n", BADLY_FORMED);
        return false;
    }
    else if (ld->flag[FLAG_S] || ld->flag[FLAG_L]) {
        ld->file = cmd[i];
        return true;
    }
    else {
        ld->input = my_getnbr(cmd[i]);
        return true;
    }
    return false;
}

bool load_flag(char **cmd, hist_build_t *load)
{
    load->input = -1;
    load->file = NULL;
    for (size_t u = 0; u < 3; load->flag[u] = false, u++);
    for (size_t i = 1; cmd[i]; i++) {
        for (size_t u = 1; cmd[i][0] == '-' && cmd[i][u]; u++) {
            if (!is_flag(cmd[i][u], load))
                return false;
        }
        if (cmd[i][0] != '-') {
            return param_manage(cmd, load, i);
        }
    }
    return true;
}