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

static int open_file_write(char *filepath, redirect_mode_out_t redirect_mode)
{
    int flags = O_CREAT | O_WRONLY;
    int fd;

    if (redirect_mode == TO_OUT) {
        flags = flags | O_TRUNC;
    } else if (redirect_mode == TO_OUT_ADD) {
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

    fd = open(filepath, flags);
    if (fd == -1) {
        show_error(filepath);
        return -1;
    }
    return fd;
}

void redirection_open_file(cmd_t *cmd)
{
    if (cmd->red_mode_out == TO_OUT || cmd->red_mode_out == TO_OUT_ADD) {
        cmd->file_fd_out = open_file_write(cmd->redirect_out[1],
                                            cmd->red_mode_out);
        if (cmd->file_fd_out == -1) {
            cmd->err = true;
            return;
        }
    }
    if (cmd->red_mode_in == FROM_IN) {
        cmd->file_fd_in = open_file_read(cmd->redirect_in[1]);
        if (cmd->file_fd_in == -1) {
            cmd->err = true;
        }
    }
}
