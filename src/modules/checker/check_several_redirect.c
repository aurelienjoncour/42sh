/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-07T17:06:50+02:00 | Author: simon
*/

#include "shell.h"

static const char *ERR_SEVERAL_REDIR_OUT = "Ambiguous output redirect.\n";
static const char *ERR_SEVERAL_REDIR_IN = "Ambiguous input redirect.\n";

static bool check_error(size_t nb_redirect_in, size_t nb_redirect_out)
{
    if (nb_redirect_out > 1) {
        fprintf(stderr, "%s", ERR_SEVERAL_REDIR_OUT);
        return true;
    } else if (nb_redirect_in > 1) {
        fprintf(stderr, "%s", ERR_SEVERAL_REDIR_IN);
        return true;
    }
    return false;
}

bool have_several_redirection(cmd_t *cmd)
{
    size_t nb_redirect_out = 0;
    size_t nb_redirect_in = 0;

    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (ptr->id == ID_DOUBLE_RIGHT || ptr->id == ID_RIGHT) {
            nb_redirect_out++;

        } else if (ptr->id == ID_DOUBLE_LEFT || ptr->id == ID_LEFT) {
            nb_redirect_in++;
        }
        if (check_error(nb_redirect_in, nb_redirect_out) == true) {
            return true;
        }
        if (ptr->id == ID_PIPE || ptr->type == D_SEPARATOR) {
            nb_redirect_out = 0;
            nb_redirect_in = 0;
        }
    }
    return false;
}
