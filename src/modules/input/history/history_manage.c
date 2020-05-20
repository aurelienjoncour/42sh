/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "history_t.h"

static int open_history(int *fd)
{
    if (access(".42history", F_OK) == -1)
        *fd = open(".42history", O_RDWR | O_CREAT, 0664);
    else
        *fd = open(".42history", O_RDWR | O_APPEND);
    if (*fd < 0)
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