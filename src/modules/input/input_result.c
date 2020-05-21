/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** manage input result
*/

#include "shell.h"
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
    if (ch == 0 || ch == 4 || ch == '\n')
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

int input_result(int ch, shell_t *shell, char **line, size_t *pos)
{
    int auto_comp = check_tab(line, pos, ch, &shell->env);

    if (auto_comp == EXIT_ERROR || ctrl_d_manage(ch, shell, *line, pos))
        return EXIT_ERROR;
    if (!move_in_line(pos, ch, line, &shell->history)
    && is_correct_char(ch)) {
        *line = add_char(*line, ch, (*pos)++);
        if (*line == NULL)
            return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}