/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include "shell.h"

bool flag_save(hist_build_t *ld, history_t *hist)
{
    int fd;
    int tmp;

    if (access(ld->file, F_OK) == -1)
        fd = open(ld->file, O_RDWR | O_CREAT, 0664);
    else
        fd = open(ld->file, O_RDWR | O_APPEND);
    if (fd < 0)
        return false;
    tmp = hist->fd;
    hist->fd = fd;
    write_history(hist);
    hist->fd = tmp;
    close(fd);
    return true;
}

static bool fd_load(hist_build_t *load, history_t *ld)
{
    if (access(load->file, F_OK) == 0)
        ld->fd = open(load->file, O_RDONLY);
    else {
        return false;
    }
    if (ld->fd < 0)
        return false;
    return true;
}

bool flag_load(hist_build_t *load, shell_t *shell)
{
    history_t ld;

    if (!fd_load(load, &ld))
        return false;
    ld.size = 0;
    ld.pos = 0;
    ld.history = read_file(ld.fd);
    if (!ld.history)
        return false;
    ld.size = get_history_size(ld.history);
    if (ld.size % 2 != 0)
        return false;
    ld.pos = (ld.size) ? ld.size - 1 : 0;
    ld.date = malloc(sizeof(date_t) * (ld.size / 2));
    ld.size /= 2;
    if (!ld.date)
        return false;
    history_build(&shell->history);
    shell->history = ld;
    return true;
}