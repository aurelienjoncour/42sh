/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "shell.h"

void save_in_hist(char **line, history_t *hist)
{
    if (!(*line)) {
        *line = malloc(sizeof(char) * 1);
        (*line)[0] = '\0';
    }
    else
        hist->history = history_manage(hist->history, *line);
}