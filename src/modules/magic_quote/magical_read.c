/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 43sh
*/

#include "shell.h"

static bool exec_quote(shell_t *shell, char *entry, int *pipefd)
{
    int save = dup(1);

    if (save == -1)
        return false;
    close(pipefd[0]);
    if (dup2(pipefd[1], 1) == -1)
        return false;
    shell_exec(shell, entry);
    if (dup2(save, 1) == -1)
        return false;
    close(pipefd[1]);
    return true;
}

static char *read_quote(int *pipefd)
{
    char buf[BUF_SIZE];
    char *ret = NULL;
    int a = 1;

    close(pipefd[1]);
    while (a > 0) {
        a = read(pipefd[0], buf, BUF_SIZE);
        if (a < 0)
            return NULL;
        buf[a] = '\0';
        ret = space_cat(ret, buf);
        if (!ret)
            return NULL;
    }
    close(pipefd[0]);
    if (my_strlen(ret) != 0 && ret[my_strlen(ret) - 1] == ' ')
        ret[my_strlen(ret) - 1] = '\0';
    return ret;
}

static int child_process_work(shell_t *par, char *entry, int *fd)
{
    shell_t new;
    int status;

    if (shell_create(&new, par->env.var, NULL) == EXIT_ERROR) {
        exit(1);
    } else if (!exec_quote(&new, entry, fd)) {
        exit(1);
    }
    status = new.exit_status;
    shell_destroy(&new);
    exit(status);
    return SUCCESS_STATUS;
}

static int parent_process_work(int *fd, char **ptr_ret)
{
    int exit_stat;
    int wstatus;

    *ptr_ret = read_quote(fd);
    if (wait(&wstatus) == -1) {
        return ERROR_STATUS;
    }
    exit_stat = child_exit_status(wstatus);
    if (exit_stat != 0) {
        return exit_stat;
    }
    return SUCCESS_STATUS;
}

int get_magic_quote(shell_t *par, char **ptr_token)
{
    int fd[2];
    pid_t pid;
    char *ret = NULL;
    int exit;

    if (pipe(fd) == -1) {
        return ERROR_STATUS;
    }
    pid = fork();
    if (pid == -1)
        return ERROR_STATUS;
    if (pid == 0) {
        return child_process_work(par, (*ptr_token), fd);
    } else {
        exit = parent_process_work(fd, &ret);
        free(*ptr_token);
        *ptr_token = ret;
        return exit;
    }
}
