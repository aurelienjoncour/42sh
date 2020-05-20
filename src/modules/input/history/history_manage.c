/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include <sys/stat.h>
#include <fcntl.h>
#include "history_t.h"
#include "shell.h"

static bool open_history(int *fd)
{
    char *homedir = get_home_path();
    char *filepath = NULL;

    if (homedir == NULL)
        return false;
    filepath = my_str_concat(homedir, "/.42history");
    free(homedir);
    if (filepath == NULL)
        return false;
    if (access(filepath, F_OK) == -1)
        *fd = open(filepath, O_RDWR | O_CREAT, 0664);
    else
        *fd = open(filepath, O_RDWR | O_APPEND);
    free(filepath);
    if (*fd <= 0)
        return false;
    return true;
}

size_t get_history_size(char **hist)
{
    size_t i;

    for (i = 0; hist[i]; i++);
    return i;
}

bool init_history(history_t *hist)
{
    hist->size = 0;
    hist->pos = 0;
    if (!open_history(&hist->fd))
        return false;
    hist->history = read_file(hist->fd);
    if (!hist->history)
        return false;
    hist->size = get_history_size(hist->history);
    if (hist->size % 2 != 0)
        return false;
    hist->pos = (hist->size) ? hist->size - 1 : 0;
    hist->date = malloc(sizeof(date_t) * (hist->size / 2));
    hist->size /= 2;
    if (!hist->date)
        return false;
    history_build(hist);
    return true;
}

void destroy_history(history_t *hist)
{
    free(hist->date);
    close(hist->fd);
    destroy_file(hist->history);
}