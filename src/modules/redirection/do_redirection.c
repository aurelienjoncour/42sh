/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-08T14:10:49+02:00 | Author: simon
*/

#include "shell.h"

int do_redirection(cmd_t *cmd)
{
    // if (cmd->red_mode_in == FROM_IN) {
    //     if (dup2(cmd->file_fd_in, 0) == -1)
    //         return puterr("dup2 (fd in) : fail\n", EXIT_ERROR);
    // }
    // if (cmd->red_mode_out == TO_OUT || cmd->red_mode_out == TO_OUT_ADD) {
    //     if (dup2(cmd->file_fd_out, 1) == -1)
    //         return puterr("dup2 (fd out) : fail\n", EXIT_ERROR);
    // }
    // if (cmd->red_mode_in == FROM_STDIN) {
    //     if (redirect_stdin_to_command(cmd->redirect_in[1], cmd) != 0) {
    //         return EXIT_ERROR;
    //     }
    // }
    return EXIT_SUCCESS;
}
