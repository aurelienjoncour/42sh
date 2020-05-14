/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-15T17:49:09+02:00 | Author: simon
*/

#include "shell.h"

static const char *ERR_AMBIG_IN = "Ambiguous input redirect.\n";
static const char *ERR_AMBIG_OUT = "Ambiguous output redirect.\n";

static bool check_error(token_t *ptr, bool have_rd_right, int nb_pipe)
{
    if (ptr->id == ID_PIPE && have_rd_right == true) {
        my_putstr_error(ERR_AMBIG_OUT);
        return true;
    }
    if ((ptr->id == ID_DOUBLE_LEFT || ptr->id == ID_LEFT) && nb_pipe > 0) {
        my_putstr_error(ERR_AMBIG_IN);
        return true;
    }
    return false;
}

bool check_position_redirection_in_pipe(cmd_t *cmd)
{
    int nb_pipe = 0;
    bool have_rd_right = false;

    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (ptr->id == ID_PIPE) {
            nb_pipe++;
        } else if (ptr->type == D_SEPARATOR) {
            nb_pipe = 0;
            have_rd_right = false;
        }
        if (check_error(ptr, have_rd_right, nb_pipe) == true) {
            return true;
        }
        if (ptr->id == ID_DOUBLE_RIGHT || ptr->id == ID_RIGHT) {
            have_rd_right = true;
        }
    }
    return false;
}
