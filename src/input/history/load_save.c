/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
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

static int get_file_size(char const *filepath)
{
    struct stat test;

    if (stat(filepath, &test) == -1)
        return -1;
    return test.st_size;
}

static char *files_read(char const *filepath, int *fd)
{
    char *temp;
    int file_size;

    *fd = open(filepath, O_RDONLY);
    if (*fd == -1)
        return NULL;
    file_size = get_file_size(filepath);
    if (file_size == -1 || file_size == 0)
        return NULL;
    temp = malloc(sizeof(char) * (file_size + 1));
    if (temp == NULL)
        return NULL;
    temp[file_size] = '\0';
    if (read(*fd, temp, file_size) < 0)
        return NULL;
    return temp;
}

bool flag_load(hist_build_t *load, shell_t *shell)
{
    history_t ld;
    char *file = files_read(load->file, &ld.fd);

    ld.size = 0;
    ld.pos = 0;
    if (!file)
        return false;
    ld.history = my_str_to_word_array(file, "\n");
    if (!ld.history)
        return false;
    ld.size = get_history_size(ld.history) - 1;
    if (ld.size % 2 != 0)
        return false;
    ld.pos = (ld.size) ? ld.size - 1 : 0;
    ld.date = malloc(sizeof(date_t) * (ld.size / 2));
    ld.size /= 2;
    if (!ld.date)
        return false;
    history_build(&ld);
    shell->history = ld;
    return true;
}