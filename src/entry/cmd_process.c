/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-03-31T15:04:50+02:00 | Author: simon
*/

#include "shell.h"

static int set_error(shell_t *shell, cmd_t *cmd)
{
    cmd_destroy(cmd);
    shell->exit_status = ERROR_STATUS;
    return EXIT_SUCCESS;
}

/*
    TODO : REFACTO
*/
int cmd_process(shell_t *shell, char *command)
{
    cmd_t cmd;

    cmd_create(&cmd, command);
    command_parse(&cmd);
    if (cmd.err == true) {
        return set_error(shell, &cmd);
    }
    redirection_open_file(&cmd);
    if (cmd.err == true) {
        return set_error(shell, &cmd);
    }
    if (do_redirection(&cmd) == EXIT_ERROR) {
        shell->exit_status = ERROR_STATUS;
        return EXIT_SUCCESS;
    }
    shell_exec_cmd(shell, cmd.cmd);
    cmd_destroy(&cmd);
    return shell->exit_status;
}
