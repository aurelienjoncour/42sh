/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-02T16:00:49+02:00 | Author: simon
*/

#include "shell.h"

int shell_exec(shell_t *shell, char *entry)
{
    cmd_t *cmd;
    
    cmd = parse_entry(entry);
    if (entry_checker(shell, cmd, entry) == EXIT_ERROR) {
        return EXIT_SUCCESS;
    }
    // TODO : substitute variables
    // <====
    free(entry);
    if (shell_exec_segment(shell, cmd) != EXIT_SUCCESS) {
        return EXIT_ERROR;
    }
    cmd_destroy(cmd);
    return EXIT_SUCCESS;
}
