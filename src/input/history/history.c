/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "shell.h"

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
}

static void c_flag(shell_t *shell)
{
    shell->history.history[0] = NULL;
    shell->history.size = 0;
}

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
    if (load.flag[FLAG_L] || load.flag[FLAG_S]) {
        if (load.flag[FLAG_L])
            flag_load(&load, shell);
        if (load.flag[FLAG_S])
            flag_save(&load, &shell->history);
        return 0;
    }
    if (!load.flag[FLAG_C])
        execute_flag(&load, &shell->history);
    else c_flag(shell);
    return 0;
}