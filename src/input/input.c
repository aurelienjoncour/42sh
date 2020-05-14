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

static bool is_correct_char(int ch)
{
    if (ch == UP || ch == DOWN)
        return false;
    if (ch == LEFT || ch == RIGHT)
        return false;
    if (ch == SUPPR_DC || ch == SUPPR || ch == GO_END || ch == GO_START)
        return false;
    return true;
}

static void select_hist(char **line, int ch, history_t *hist, size_t *pos)
{
    /*if (*line)
        free(*line);*/
    if (ch == UP) {
        if (hist->pos > 0) {
            hist->pos--;
            *line = my_strdup(hist->history[hist->pos]);
        }
    }
    else if (ch == DOWN) {
        if (hist->history[hist->pos] && hist->history[hist->pos + 1]) {
            hist->pos++;
            *line = my_strdup(hist->history[hist->pos]);
        }
        else
            *line = NULL;
    }
    if (*line)
        *pos = my_strlen(*line);
}

static bool move_in_line(size_t *pos, int ch, char **line, history_t *hist)
{
    if (ch == UP || ch == DOWN)
        select_hist(line, ch, hist, pos);
    if (!*line)
        return false;
    if (*pos != 0 && ch == LEFT) {
        *pos -= 1;
        return true;
    }
    if (*pos < (size_t) my_strlen(*line) && ch == RIGHT) {
        *pos += 1;
        return true;
    }
    if (ch == SUPPR_DC || ch == SUPPR)
        rm_char(*line, pos, (ch == SUPPR) ? false : true);
    if (ch == GO_END)
        *pos = my_strlen(*line);
    if (ch == GO_START)
        *pos = 0;
    return false;
}

static void display_line(char *line)
{
    if (line)
        fprintf(stdout, "\33[2K\r$> %s", line);
    else
        fprintf(stdout, "\33[2K\r$> ");
    fflush(stdout);
}

char *term_input(history_t *hist)
{
    size_t pos = 0;
    int ch = 0;
    char *line = NULL;

    hist->pos = get_history_size(hist->history);
    while (ch != '\n') {
        display_line(line);
        ch = my_getch();
        if (!move_in_line(&pos, ch, &line, hist) && is_correct_char(ch)) {
            line = add_char(line, ch, pos);
            pos++;
            if (!line)
                return NULL;
        }
    }
    hist->history = history_manage(hist->history, line);
    my_putchar('\n');
    return line;
}