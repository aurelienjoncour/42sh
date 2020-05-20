/*
** EPITECH PROJECT, 2020
** PROJECT_NAME
** File description:
** Created: 2020-05-18T20:41:22+02:00 | Author: simon
*/

#include "shell.h"

static token_t *get_parenthesis(cmd_t *cmd)
{
    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (ptr->id == ID_PARENTHESE) {
            return ptr;
        }
    }
    return NULL;
}

static void child_work(char *token, shell_t *parent_shell)
{
    char *entry = my_strndup(token + 1, strlen(token) - 2);
    shell_t shell;

    if (shell_create(&shell, parent_shell->env.var, NULL) == EXIT_ERROR) {
        exit(EXIT_ERROR);
    } else if (!entry) {
        exit(EXIT_ERROR);
    }
    if (shell_exec(&shell, entry) == EXIT_ERROR) {
        exit(EXIT_ERROR);
    }
    shell_destroy(&shell);
    exit(shell.exit_status);
}

static int process_parenthesis(shell_t *shell, char *token)
{
    pid_t pid;
    int wstatus = 0;

    pid = fork();
    if (pid == -1) {
        return puterr("fork : fail\n", EXIT_ERROR);
    } else if (pid == 0) {
        child_work(token, shell);
    } else {
        pid = wait(&wstatus);
        if (pid == -1) {
            return puterr("wait : fail", EXIT_ERROR);
        }
        shell->exit_status = child_exit_status(wstatus);
    }
    return EXIT_SUCCESS;
}

int parenthesis_exec(shell_t *shell, cmd_t *cmd)
{
    token_t *tok_parenthesis = get_parenthesis(cmd);

    if (tok_parenthesis == NULL) {
        return EXIT_FAIL;
    }
    if (process_parenthesis(shell, tok_parenthesis->token) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
