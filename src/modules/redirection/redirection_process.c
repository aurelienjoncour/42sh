/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-14T14:34:46+02:00 | Author: simon
*/

#include "shell.h"

bool is_redirect_type(redirect_t *redirect, REDIRECT_TYPE compare)
{
    if ((redirect->type & compare) != 0) {
        return true;
    }
    return false;
}

bool token_is_file_redirect(ID id)
{
    if (id == ID_DOUBLE_RIGHT || id == ID_RIGHT || id == ID_LEFT
        || id == ID_DOUBLE_LEFT) {
        return true;
    }
    return false;
}

static REDIRECT_TYPE get_redirected_type(ID id)
{
    switch (id) {
        case ID_DOUBLE_RIGHT:
            return R_DRIGHT;
            break;
        case ID_RIGHT:
            return R_RIGHT;
            break;
        case ID_LEFT:
            return R_LEFT;
            break;
        case ID_DOUBLE_LEFT:
            return R_DLEFT;
            break;
        default:
            return NO_REDIRECT;
    }
}

static void get_redirection_data(cmd_t *cmd, redirect_t *redirect)
{
    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (token_is_file_redirect(ptr->id) == false) {
            continue;
        }
        redirect->type = redirect->type | get_redirected_type(ptr->id);
        if ((ptr->id == ID_RIGHT || ptr->id == ID_DOUBLE_RIGHT) && ptr->next) {
            redirect->filename_right = my_strdup(ptr->next->token);
        } else if ((ptr->id == ID_LEFT || ptr->id == ID_DOUBLE_LEFT)
                && ptr->next) {
            redirect->string_left = my_strdup(ptr->next->token);
        }
    }
}

int redirection_process(cmd_t *cmd, redirect_t *ptr_redirect)
{
    ptr_redirect->type = 0;
    ptr_redirect->string_left = NULL;
    ptr_redirect->filename_right = NULL;
    ptr_redirect->fd_left = 0;
    ptr_redirect->fd_right = 0;
    ptr_redirect->pipe_redirect[0] = 0;
    get_redirection_data(cmd, ptr_redirect);
    if (redirection_open_file(ptr_redirect) == EXIT_ERROR) {
        return EXIT_FAIL;
    } else if (do_redirection(ptr_redirect) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
