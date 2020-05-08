/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-03-31T15:04:50+02:00 | Author: simon
*/

#include "shell.h"

static const char *ERR_NULL_CMD = "Invalid null command.\n";

static void wait_end_all_child_process(void)
{
    int wstatus;
    pid_t pid;

    do {
        pid = wait(&wstatus);
    } while (pid != -1);
}

static int process_all_pipe(shell_t *shell, char **piped_cmd)
{
    bool is_last = false;

    shell->fd.prev_pipein = -1;
    for (size_t i = 0; piped_cmd[i] != NULL; i++) {
        if (piped_cmd[i + 1] == NULL) {
            is_last = true;
        }
        if (is_last && pipe_process_cmd_last(shell, piped_cmd[i]) != 0) {
            return EXIT_ERROR;
        }
        if (!is_last && pipe_process_cmd(shell, piped_cmd[i]) != 0) {
            return EXIT_ERROR;
        }
    }
    wait_end_all_child_process();
    return EXIT_SUCCESS;
}

int shell_exec_piped(shell_t *shell, char *sub_entry)
{
    char **piped_cmd = my_str_to_word_array(sub_entry, "|");

    if (!piped_cmd) {
        return EXIT_ERROR;
    }
    if (word_array_have_empty_str(piped_cmd) == true) {
        shell->exit_status = ERROR_STATUS;
        my_putstr(ERR_NULL_CMD);
        return EXIT_SUCCESS;
    } else if (process_all_pipe(shell, piped_cmd) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    word_array_destroy(piped_cmd);
    return EXIT_SUCCESS;
}
