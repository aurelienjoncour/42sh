/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** function
*/

#include "minishell.h"

static void sub_process(char **cmd, minishell_t *shell)
{
    int ret = execve(cmd[0], cmd, shell->env.var);
    char *err_msg = NULL;

    if (ret == -1) {
        my_putstr_error(cmd[0]);
        if (errno == ENOEXEC) {
            my_putstr_error(": Exec format error. Wrong Architecture.\n");
        } else {
            err_msg = strerror(errno);
            if (err_msg) {
                my_putstr_error(": ");
                my_putstr_error(err_msg);
                my_putstr_error(".\n");
            }
        }
        shell->exit_status = ERROR_STATUS;
    } else {
        shell->exit_status = SUCCESS_STATUS;
    }
}

static void child_exit_status(int wstatus, minishell_t *shell)
{
    if (!wstatus) {
        shell->exit_status = SUCCESS_STATUS;
        return;
    }
    if (WIFSIGNALED(wstatus) && wstatus == 8) {
        my_putstr_error("Floating exception");
        shell->exit_status = DIVZERO_STATUS;
    } else if (WIFSIGNALED(wstatus)) {
        my_putstr_error("Segmentation fault");
        shell->exit_status = SEGFAULT_STATUS;
    }
    if (WIFSIGNALED(wstatus) && WCOREDUMP(wstatus)) {
        my_putstr_error(" (core dumped)");
    }
    if (WIFSIGNALED(wstatus)) {
        my_putstr_error("\n");
    } else if (WIFEXITED(wstatus)) {
        shell->exit_status = WEXITSTATUS(wstatus);
    }
}

int fork_process(char **cmd, minishell_t *shell)
{
    pid_t pid;
    int wstatus = 0;
    pid_t ret;

    pid = fork();
    if (pid == 0) {
        sub_process(cmd, shell);
        exit(shell->exit_status);
    } else if (pid < 0) {
        my_putstr_error("fork : Fail.\n");
        return EXIT_ERROR;
    } else {
        ret = waitpid(pid, &wstatus, 0);
        if (ret == -1) {
            my_putstr_error("waitpid: Fail.\n");
        }
        child_exit_status(wstatus, shell);
    }
    return EXIT_SUCCESS;
}

int minishell_exec_bin_cmd(char **cmd, minishell_t *shell)
{
    char *save_cmd_head = cmd[0];

    if (get_bin_path(&cmd, shell) == EXIT_FAIL) {
        return EXIT_FAIL;
    }
    if (fork_process(cmd, shell) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    if (save_cmd_head[0] == 0)
        free(cmd[0]);
    return EXIT_SUCCESS;
}
