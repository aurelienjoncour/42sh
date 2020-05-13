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

    char **cmd = my_str_to_word_array(entry, " "); // DEBUG
    shell_exec_cmd(shell, cmd); // DEBUG

    // TODO : fredou parser (+ cleaner)

    // TODO : substitute variables

    // TODO : entry checker (error)

    free(entry);
    if (shell_exec_segment(shell, cmd) != EXIT_SUCCESS) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
