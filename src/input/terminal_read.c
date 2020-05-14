/*
** EPITECH PROJECT, 2019
** minishell
** File description:
** minishell
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"
#include "my.h"

static char *classic_input(void)
{
    char *line = NULL;
    size_t size;
    int read_val;

    read_val = getline(&line, &size, stdin);
    if (read_val <= 0 || !line) {
        if (line)
            free(line);
        return NULL;
    }
    return line;
}

char *terminal_read(history_t *hist)
{
    char *line = NULL;
    int rd_val;

    if (isatty(0) != 1)
        line = classic_input();
    else
        line = term_input(hist);
    if (!line)
        return NULL;
    rd_val = my_strlen(line);
    if (rd_val != 0 && line[rd_val - 1] == '\n')
        line[rd_val - 1] = '\0';
    return line;
}