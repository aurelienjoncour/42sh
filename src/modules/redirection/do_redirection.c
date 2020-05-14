/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-08T14:10:49+02:00 | Author: simon
*/

#include "shell.h"

int do_redirection(redirect_t *redirect)
{
    if (is_redirect_type(redirect, R_LEFT)) {
        if (dup2(redirect->fd_left, 0) == -1)
            return puterr("dup2 (fd left) : fail\n", EXIT_ERROR);
    }
    if (is_redirect_type(redirect, R_RIGHT)
            || is_redirect_type(redirect, R_DRIGHT)) {
        if (dup2(redirect->fd_right, 1) == -1)
            return puterr("dup2 (fd right) : fail\n", EXIT_ERROR);
    }
    if (is_redirect_type(redirect, R_DLEFT)) {
        if (redirect_stdin_to_command(redirect) != EXIT_SUCCESS) {
            return EXIT_ERROR;
        }
    }
    return EXIT_SUCCESS;
}
