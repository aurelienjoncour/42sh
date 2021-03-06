/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-03-31T15:04:50+02:00 | Author: simon
*/

#include "shell.h"

static int child_close_pipe_redirection(fd_t *fd)
{
    if (close(fd->pipe_fd[0]) == -1) {
        return puterr("close fd[0] : fail\n", EXIT_ERROR);
    }
    if (close(fd->pipe_fd[1]) == -1) {
        return puterr("close fd[1] : fail\n", EXIT_ERROR);
    }
    return EXIT_SUCCESS;
}

static int child_create_pipe_redirection(fd_t *fd)
{
    if (fd->prev_pipein != -1) {
        if (dup2(fd->prev_pipein, 0) == -1) {
            return puterr("dup2 : fail\n", EXIT_ERROR);
        }
    }
    if (dup2(fd->pipe_fd[1], 1) == -1) {
        return puterr("dup2 : fail\n", EXIT_ERROR);
    }
    return EXIT_SUCCESS;
}

static int child_process_work(shell_t *shell, cmd_t *pipe_cmd)
{
    if (child_create_pipe_redirection(&shell->fd) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    if (shell_exec_boolop(shell, pipe_cmd) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    if (child_close_pipe_redirection(&shell->fd) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    shell_exit(shell, shell->exit_status);
    return EXIT_SUCCESS;
}

static int parent_process_redirect_manage(fd_t *fd)
{
    if (fd->prev_pipein != -1) {
        close(fd->prev_pipein);
    }
    fd->prev_pipein = fd->pipe_fd[0];
    if (close(fd->pipe_fd[1]) == -1) {
        return puterr("close fd[1] : fail\n", EXIT_ERROR);
    }
    return EXIT_SUCCESS;
}

int pipe_process_cmd(shell_t *shell, cmd_t *pipe_cmd)
{
    pid_t cpid;

    if (pipe(shell->fd.pipe_fd) == -1) {
        return puterr("pipe : fail\n", EXIT_ERROR);
    }
    cpid = fork();
    if (cpid == -1) {
        return puterr("fork : fail\n", EXIT_ERROR);
    } else if (cpid != 0) {
        if (parent_process_redirect_manage(&shell->fd) != 0) {
            return EXIT_ERROR;
        }
    } else {
        if (child_process_work(shell, pipe_cmd) != EXIT_SUCCESS) {
            return EXIT_ERROR;
        }
    }
    return EXIT_SUCCESS;
}
