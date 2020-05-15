/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "shell.h"

#define BADLY_FORMED "history: Badly formed number."
#define USAGE_HISTORY "Usage: history [-chrSLMT] [# number of events]."
#define FEW_ARG "history: Too many arguments."

static void display_history(size_t start, history_t *hist)
{
    for (size_t i = start; hist->history[i]; i++)
        fprintf(stdout, "%5li %02i:%02i %s\n", i + 1, hist->date[i].hours,
            hist->date[i].minutes, hist->history[i]);
}

static int  flag_manage(shell_t *shell, char **cmd)
{
    if (my_strcmp("-c", cmd[1]) == 0) {
        shell->history.history[0] = NULL;
        return 0;
    }
    fprintf(stderr, "%s\n", USAGE_HISTORY);
    return 1;
}

int built_in_history(char **cmd, shell_t *shell)
{
    int arg = word_array_len(cmd);
    size_t size = word_array_len(shell->history.history);

    if (arg >= 3) {
        fprintf(stderr, "%s\n", FEW_ARG);
        return 1;
    }
    if (arg > 1 && cmd[1][0] == '-')
        return flag_manage(shell, cmd);
    else if (arg > 1)
        if (my_str_isnum(cmd[1]) == 1) {
            if ((int) size - my_getnbr(cmd[1]) >= 0)
                display_history(size - my_getnbr(cmd[1]), &shell->history);
            else display_history(0, &shell->history);
        }
        else {
            fprintf(stderr, "%s\n", BADLY_FORMED);
            return 1;
        }
    else display_history(0, &shell->history);
    return 0;
}