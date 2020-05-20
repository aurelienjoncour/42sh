/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 43sh
*/

#include "shell.h"

char *space_cat(char *str, char *src)
{
    size_t size = (str) ? strlen(str) + strlen(src) : strlen(src);
    char *new = malloc(sizeof(char) * (size + 1));
    size_t move = 0;

    if (str) {
        for (size_t i = 0; str[i]; i++)
            new[move++] = str[i];
        free(str);
    }
    for (size_t i = 0; src[i]; i++)
        if (src[i] == '\n')
            src[i] = ' ';
    for (size_t i = 0; src[i]; i++)
        new[move++] = src[i];
    new[move] = '\0';
    return new;
}

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
    }
    close(pipefd[0]);
    if (ret[strlen(ret) - 1] == ' ')
        ret[strlen(ret) - 1] = '\0';
    return ret;
}

char *get_magic_quote(shell_t *shell, char *entry)
{
    int pipefd[2];
    pid_t pid;
    char *ret = NULL;

    if (pipe(pipefd) == -1)
        return NULL;
    pid = fork();
    if (pid == -1)
        return NULL;
    if (pid == 0) {
        if (!exec_quote(shell, entry, pipefd))
            return NULL;
        exit(1);
    } else {
        ret = read_quote(pipefd);
    }
    wait(NULL);
    return ret;
}