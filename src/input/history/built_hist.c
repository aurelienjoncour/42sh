/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "shell.h"

static void struct_filler(date_t *data, char *line)
{
    ssize_t pos = my_strlen(line) - 1;

    for (; pos >= 0 && line[pos] != ':'; pos--);
    data->minutes = my_getnbr(line + pos);
    line[pos] = '\0';
    data->hours = my_getnbr(line + 2);
}

static void rm_line(char **tab, size_t pos)
{
    free(tab[pos]);
    for (size_t i = pos; tab[i]; i++)
        tab[i] = tab[i + 1];
}

void history_build(history_t *hist)
{
    size_t move = 0;

    for (size_t i = 0; hist->history[i]; i++) {
        if (hist->history[i][0] != '\0') {
            struct_filler(&hist->date[move], hist->history[i]);
            rm_line(hist->history, i);
            move++;
        }
        else {
            rm_line(hist->history, i);
        }
    }
}