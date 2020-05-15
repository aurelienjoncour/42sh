/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-03-31T15:04:50+02:00 | Author: simon
*/

#include "shell.h"

int cmd_process(shell_t *shell, cmd_t *cmd)
{
    char **warray_cmd;
    redirect_t redirect;

    // TODO : file redirection
    if (redirection_process(cmd, &redirect) != EXIT_SUCCESS) {
        clean_redirect(&redirect);
        shell->exit_status = ERROR_STATUS;
        return EXIT_SUCCESS;
    }

    // TODO : job control
    // <=====

    //--call : magic quotes exec
    // <=====

    //--call : exec cmd
    warray_cmd = linked_list_to_warray(cmd);
    if (!warray_cmd)
        return puterr("warray cmd : error\n", EXIT_ERROR);
    if (shell_exec_cmd(shell, warray_cmd) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    word_array_destroy(warray_cmd);
    clean_redirect(&redirect);

    //--call : parenthesis exec
    // <=====
    return EXIT_SUCCESS;
}
