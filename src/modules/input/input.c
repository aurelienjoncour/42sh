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

static bool is_correct_char(int ch)
{
    if (ch == UP || ch == DOWN)
        return false;
    if (ch == LEFT || ch == RIGHT)
        return false;
    if (ch == SUPPR_DC || ch == SUPPR || ch == GO_END || ch == GO_START
    || ch == STAB)
        return false;
    if (ch == 0)
        return false;
    return true;
}

static void select_hist(char **line, int ch, history_t *hist, size_t *pos)
{
    if (*line && ((hist->pos > 0 && ch == UP) ||
    (ch == DOWN && hist->history[hist->pos] && hist->history[hist->pos + 1])))
        free(*line);
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
        else {
            *line = NULL;
            hist->pos = get_history_size(hist->history);
        }
    }
    *pos = (*line) ? my_strlen(*line) : 0;
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

static void display_line(shell_t *shell, char *line, size_t pos)
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
    int auto_comp;

    shell->history.pos = get_history_size(shell->history.history);
    while (ch != '\n') {
        display_line(shell, line, pos);
        ch = my_getch();
        auto_comp = check_tab(&line, &pos, ch, &shell->env);
        if (auto_comp == EXIT_ERROR)
            return NULL;
        if (!move_in_line(&pos, ch, &line, &shell->history)
        && is_correct_char(ch)) {
            line = add_char(line, ch, pos++);
            if (!line)
                return NULL;
        }
        if (ch == STAB && auto_comp == EXIT_SUCCESS)
            return term_input(shell, line, pos);
    }
    my_putchar('\n');
    save_in_hist(&line, &shell->history);
    return line;
}