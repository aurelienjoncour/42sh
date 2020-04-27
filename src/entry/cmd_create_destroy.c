/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** Created: 2020-04-08T09:15:52+02:00 | Author: simon
*/

#include "minishell.h"

static void reset_file_redirect_from_stdin(cmd_t *cmd)
{
    if (cmd->red_mode_in == FROM_STDIN) {
        if (close(cmd->pipe_redirect[0]) == -1) {
            puterr("close pipe_red[0] : fail\n", 0);
        }
    }
}

static void destroy_cmd_redirection_and_fd(cmd_t *cmd)
{
    if (cmd->redirect_in != NULL) {
        free(cmd->redirect_in);
    }
    if (cmd->redirect_out != NULL) {
        free(cmd->redirect_out);
    }
    if (cmd->file_fd_in != -1) {
        close(cmd->file_fd_in);
    }
    if (cmd->file_fd_out != -1) {
        close(cmd->file_fd_out);
    }
}

void cmd_destroy(cmd_t *cmd)
{
    cmd->command = NULL;
    free(cmd->formatted);
    if (cmd->wa != NULL) {
        word_array_destroy(cmd->wa);
    }
    if (cmd->cmd != NULL) {
        free(cmd->cmd);
    }
    destroy_cmd_redirection_and_fd(cmd);
    reset_file_redirect_from_stdin(cmd);
}

void cmd_create(cmd_t *cmd, char *command)
{
    cmd->command = command;
    cmd->formatted = NULL;
    cmd->wa = NULL;
    cmd->cmd = NULL;
    cmd->redirect_in = NULL;
    cmd->redirect_out = NULL;
    cmd->err = false;
    cmd->red_mode_in = NO_IN_REDIRECT;
    cmd->red_mode_out = NO_OUT_REDIRECT;
    cmd->file_fd_in = -1;
    cmd->file_fd_out = -1;
}
