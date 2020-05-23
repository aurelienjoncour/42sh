/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-03-31T15:04:50+02:00 | Author: simon
*/

#include "shell.h"

static int prepare_processing(shell_t *shell, cmd_t *cmd, redirect_t *redirect)
{
    if (substr_variables(shell, cmd) == EXIT_FAIL) {
        return EXIT_FAIL;
    }
    if (globbing(cmd, shell) == EXIT_FAIL) {
        return EXIT_FAIL;
    }
    if (redirection_process(cmd, redirect) != EXIT_SUCCESS) {
        clean_redirect(redirect, shell);
        shell->exit_status = ERROR_STATUS;
        return EXIT_FAIL;
    }
    return EXIT_SUCCESS;
}

static int cmd_process_command(shell_t *shell, cmd_t *cmd)
{
    int mq_status;
    int mq_exit_status;
    char **warray_cmd;

    mq_status = load_magic_quote(shell, cmd, &mq_exit_status);
    if (mq_status == EXIT_ERROR)
        return EXIT_ERROR;
    warray_cmd = linked_list_to_warray(cmd);
    if (!warray_cmd)
        return puterr("warray cmd : error\n", EXIT_ERROR);
    if (shell_exec_cmd(shell, warray_cmd) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    word_array_destroy(warray_cmd);
    if (mq_status == HAVE_MQUOTE && mq_exit_status != 0) {
        shell->exit_status = mq_exit_status;
    }
    return EXIT_SUCCESS;
}

int cmd_process(shell_t *shell, cmd_t *cmd)
{
    redirect_t redirect;
    int ret;

    ret = prepare_processing(shell, cmd, &redirect);
    if (ret == EXIT_ERROR) {
        return EXIT_ERROR;
    } else if (ret == EXIT_FAIL) {
        return EXIT_SUCCESS;
    }
    ret = parenthesis_exec(shell, cmd);
    if (ret == EXIT_ERROR) {
        return EXIT_ERROR;
    } else if (ret == EXIT_FAIL) {
        if (cmd_process_command(shell, cmd) == EXIT_ERROR)
            return EXIT_ERROR;
    }
    clean_redirect(&redirect, shell);
    return EXIT_SUCCESS;
}
