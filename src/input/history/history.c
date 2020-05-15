/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "shell.h"

static bool is_flag(char c, hist_build_t *load)
{
    char flag[] = "crh";

    for (size_t i = 0; flag[i]; i++)
        if (flag[i] == c) {
            load->flag[i] = true;
            return true;
        }
    fprintf(stderr, "%s\n", USAGE_HISTORY);
    return false;
}

static bool load_flag(char **cmd, hist_build_t *load)
{
    load->input = -1;
    for (size_t u = 0; u < 3; load->flag[u] = false, u++);
    for (size_t i = 1; cmd[i]; i++) {
        for (size_t u = 1; cmd[i][0] == '-' && cmd[i][u]; u++) {
            if (!is_flag(cmd[i][u], load))
                return false;
        }
        if (cmd[i][0] != '-') {
            if (my_str_isnum(cmd[i]) != 1) {
                fprintf(stderr, "%s\n", BADLY_FORMED);
                return false;
            }
            else {
                load->input = my_getnbr(cmd[i]);
                return true;
            }
        }
    }
    return true;
}

static void execute_flag(hist_build_t *ld, history_t *hist)
{
    int move = (ld->flag[FLAG_R]) ? -1 : 1;
    int start = 0;
    int end = 0;

    if (ld->input == -1) {
        start = (ld->flag[FLAG_R]) ? word_array_len(hist->history) - 1 : start;
    }
    else {
        start = word_array_len(hist->history) - ld->input;
        if (ld->flag[FLAG_R]) {
            start = word_array_len(hist->history) - 1;
            end = start - ld->input + 1;
        }
    }
    for (int i = start; i >= 0 && hist->history[i] && i >= end; i += move) {
        if (!ld->flag[FLAG_H])
            fprintf(stdout, "%5i %02i:%02i ",
                i + 1, hist->date[i].hours, hist->date[i].minutes);
        fprintf(stdout, "%s\n", hist->history[i]);
    }
}//history ra

int built_in_history(char **cmd, shell_t *shell)
{
    int arg = word_array_len(cmd);
    hist_build_t load = {0};

    if (arg > 3) {
        fprintf(stderr, "%s\n", FEW_ARG);
        return 1;
    }
    if (!load_flag(cmd, &load))
        return 1;
    if (!load.flag[FLAG_C])
        execute_flag(&load, &shell->history);
    else shell->history.history[0] = NULL;
    return 0;
}