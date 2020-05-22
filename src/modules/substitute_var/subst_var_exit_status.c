/*
** EPITECH PROJECT, 2019
** 53sh
** File description:
** 54SH
*/

#include "shell.h"

static const char *ERR_VAR_UNDEFINED = "%s: Undefined variable.\n";

int subst_exit_status(token_t *tok, size_t idx, shell_t *shell, char *varname)
{
    char tmp[12];

    if (!varname) {
        puterr("strndup : fail", EXIT_ERROR);
        return EXIT_ERROR;
    }
    if (my_strcmp(varname, "?") == 0) {
        sprintf(tmp, "%i", shell->exit_status);
        if (process_subst_value_force(varname, tok, tmp, idx) == EXIT_ERROR)
            return EXIT_ERROR;
        return EXIT_SUCCESS;
    }
    return -1;
}

int subst_exit_error(char *varname)
{
    fprintf(stderr, ERR_VAR_UNDEFINED, varname);
    free(varname);
    return EXIT_ERROR;
}