/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-08T14:10:49+02:00 | Author: simon
*/

#include "shell.h"

static const mode_t FILE_RIGHT = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

void show_error(const char *param)
{
    char *msg = strerror(errno);

    my_putstr_error(param);
    my_putstr_error(": ");
    my_putstr_error(msg);
    my_putstr_error(".\n");
}

static int open_file_write(const char *filepath, redirect_t *redirect)
{
    int flags = O_CREAT | O_WRONLY;
    int fd;

    if (!filepath) {
        return -1;
    }
    if (is_redirect_type(redirect, R_RIGHT)) {
        flags = flags | O_TRUNC;
    } else if (is_redirect_type(redirect, R_DRIGHT)) {
        flags = flags | O_APPEND;
    }
    fd = open(filepath, flags, FILE_RIGHT);
    if (fd == -1) {
        show_error(filepath);
        return -1;
    }
    return fd;
}

static int open_file_read(char *filepath)
{
    int flags = O_RDONLY;
    int fd;

    if (!filepath) {
        return -1;
    }
    fd = open(filepath, flags);
    if (fd == -1) {
        show_error(filepath);
        return -1;
    }
    return fd;
}

int redirection_open_file(redirect_t *redirect)
{
    if (is_redirect_type(redirect, R_RIGHT)
            || is_redirect_type(redirect, R_DRIGHT)) {
        redirect->fd_right = open_file_write(redirect->filename_right,
                                            redirect);
        if (redirect->fd_right == -1) {
            return EXIT_ERROR;
        }
    }
    if (is_redirect_type(redirect, R_LEFT)) {
        redirect->fd_left = open_file_read(redirect->string_left);
        if (redirect->fd_left == -1) {
            return EXIT_ERROR;
        }
    }
    return EXIT_SUCCESS;
}
