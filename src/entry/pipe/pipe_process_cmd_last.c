/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-03-31T15:04:50+02:00 | Author: simon
*/

#include "shell.h"

static int close_pipe_redirection(fd_t *fd)
{
    if (dup2(fd->stdout, 1) == -1)
        return puterr("dup2 : fail\n", EXIT_ERROR);
    if (dup2(fd->stdin, 0) == -1)
        return puterr("dup2 : fail\n", EXIT_ERROR);
    if (fd->prev_pipein != -1) {
        close(fd->prev_pipein);
    }
    if (close(fd->pipe_fd[0]) == -1) {
        return puterr("close fd[0] : fail\n", EXIT_ERROR);
    }
    if (close(fd->pipe_fd[1]) == -1) {
        return puterr("close fd[1] : fail\n", EXIT_ERROR);
    }
    return EXIT_SUCCESS;
}

static int create_pipe_redirection(fd_t *fd)
{
    if (fd->prev_pipein != -1) {
        if (dup2(fd->prev_pipein, 0) == -1) {
            return puterr("dup2 : fail\n", EXIT_ERROR);
        }
    }
    return EXIT_SUCCESS;
}

int pipe_process_cmd_last(shell_t *shell, cmd_t *pipe_cmd)
{
    if (pipe(shell->fd.pipe_fd) == -1) {
        return puterr("pipe : fail\n", EXIT_ERROR);
    }
    if (create_pipe_redirection(&shell->fd) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    if (cmd_process(shell, pipe_cmd) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    if (close_pipe_redirection(&shell->fd) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
