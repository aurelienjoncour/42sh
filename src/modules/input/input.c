/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include <stdlib.h>
#include <curses.h>
#include "shell.h"
#include "my.h"
#include "autocompletion.h"

void display_line(shell_t *shell, char *line, size_t pos)
{
    fprintf(stdout, "\33[2K\r");
    show_main_prompt(shell);
    if (line) {
        for (size_t i = 0; line[i]; i++) {
            if (i != pos)
                fprintf(stdout, "%c", line[i]);
            else fprintf(stdout, "\e[7m%c\e[27m", line[i]);
        }
    }
    fflush(stdout);
}

char *term_input(shell_t *shell, char *line, size_t pos)
{
    int ch = 0;

    shell->history.pos = get_history_size(shell->history.history);
    while (ch != '\n') {
        display_line(shell, line, pos);
        ch = my_getch(&line);
        line = input_result(ch, shell, line, &pos);
        if (line == NULL)
            return NULL;
    }
    my_putchar('\n');
    save_in_hist(&line, &shell->history);
    return line;
}