/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** function
*/

#include "shell.h"

static void sub_process_manage_ret(shell_t *shell, int ret,
char **cmd)
{
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

static void sub_process(char **cmd, shell_t *shell)
{
    int ret;
    char *path_filename[2];
    char *save_cmd = cmd[0];

    if (split_filepath(cmd[0], &path_filename[0], &path_filename[1]) != 0) {
        return;
    }
    cmd[0] = path_filename[1];
    ret = execve(save_cmd, cmd, shell->env.var);
    cmd[0] = save_cmd;
    sub_process_manage_ret(shell, ret, cmd);
    free(path_filename[0]);
    free(path_filename[1]);
}

int child_exit_status(int wstatus)
{
    int status = SUCCESS_STATUS;

    if (!wstatus)
        return SUCCESS_STATUS;
    if (WIFSIGNALED(wstatus) && wstatus == 8) {
        my_putstr_error("Floating exception");
        status = DIVZERO_STATUS;
    } else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGSEGV) {
        my_putstr_error("Segmentation fault");
        status = SEGFAULT_STATUS;
    }
    if (WIFSIGNALED(wstatus) && WCOREDUMP(wstatus)) {
        my_putstr_error(" (core dumped)");
    }
    if (WIFSIGNALED(wstatus)
            && (WTERMSIG(wstatus) == SIGSEGV || wstatus == 8)) {
        my_putstr_error("\n");
    } else if (WIFEXITED(wstatus))
        return WEXITSTATUS(wstatus);
    return status;
}

static int fork_process(char **cmd, shell_t *shell)
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
        if (ret == -1)
            my_putstr_error("waitpid: Fail.\n");
        shell->exit_status = child_exit_status(wstatus);
    }
    return EXIT_SUCCESS;
}

int shell_exec_bin_cmd(char **cmd, shell_t *shell)
{
    char *save_head = NULL;
    char *bin_path = NULL;

    if (get_bin_path(cmd[0], &bin_path, shell) != EXIT_SUCCESS) {
        return EXIT_FAIL;
    }
    save_head = cmd[0];
    cmd[0] = bin_path;
    if (fork_process(cmd, shell) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    free(bin_path);
    cmd[0] = save_head;
    return EXIT_SUCCESS;
}
