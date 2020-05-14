/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-08T15:17:25+02:00 | Author: simon
*/

#include "shell.h"

int shell_exec_segment(shell_t *shell, cmd_t *cmd)
{
    cmd_t **segments = split_cmd_list(cmd, ID_SEP, 0);

    if (!segments) {
        return EXIT_ERROR;
    }
    for (size_t i = 0; segments[i] != NULL; i++) {
       if (shell_exec_pipe(shell, segments[i]) != EXIT_SUCCESS) {
           return EXIT_ERROR;
       }
    }
    cmd_array_destroy(segments);
    return EXIT_SUCCESS;
}
