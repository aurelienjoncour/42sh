/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-03-31T15:04:50+02:00 | Author: simon
*/

#include "shell.h"

/*
    TODO : REFACTO
*/
int cmd_process(shell_t *shell, cmd_t *cmd)
{
    // TODO : file redirection
    // redirection_open_file(&cmd);
    // if (cmd.err == true) {
    //     return set_error(shell, &cmd);
    // }
    // if (do_redirection(&cmd) == EXIT_ERROR) {
    //     shell->exit_status = ERROR_STATUS;
    //     return EXIT_SUCCESS;
    // }

    // TODO : job control

    //--call : magic quotes exec

    //--call : exec cmd
    // TODO : linked list to word array
    //shell_exec_cmd(shell, cmd.cmd);

    //--call : parenthesis exec
    return shell->exit_status;
}
