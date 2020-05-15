/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-14T14:34:46+02:00 | Author: simon
*/

#include "shell.h"

void clean_redirect(redirect_t *redirect)
{
    if (redirect->string_left) {
        free(redirect->string_left);
    }
    if (redirect->filename_right) {
        free(redirect->filename_right);
    }
    if (redirect->fd_left > 0) {
        close(redirect->fd_left);
    }
    if (redirect->fd_right > 0) {
        close(redirect->fd_right);
    }
    if (redirect->pipe_redirect[0] > 0) {
        close(redirect->pipe_redirect[0]);
    }
}
