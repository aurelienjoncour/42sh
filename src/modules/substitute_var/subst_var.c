/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-18T10:21:27+02:00 | Author: simon
*/

#include "shell.h"

static const char *ERR_VAR_NAME = "Illegal variable name.\n";

static int check_variable_name(char *str)
{
    if (str == NULL || str[0] == '\0') {
        return EXIT_SUCCESS;
    }
    if (char_is_letter(str[0]) || (str[0] >= '0' && str[0] <= '9')) {
        return EXIT_SUCCESS;
    }
    if (str[0] == ' ' || str[0] == '\t' || str[0] == '_') {
        return EXIT_FAIL;
    }
    my_putstr_error(ERR_VAR_NAME);
    return EXIT_ERROR;
}

static char *get_varname(token_t *tok, size_t idx)
{
    size_t size = 0;
    char *ret = NULL;

    for (; tok->token[size + idx] != '\0'; size++) {
        if (!char_is_letter(tok->token[idx + size])
            && !(tok->token[idx + size] >= '0'
            || tok->token[idx + size] <= '9')) {
            break;
        }
    }
    ret = my_strndup(&(tok->token[idx]), size);
    return ret;
}

static int process_subst(token_t *tok, size_t idx, shell_t *shell)
{
    char *varname = get_varname(tok, idx);

    if (!varname) {
        return puterr("strndup : fail", EXIT_ERROR);
    }
    //////////////
    // TODO
    fprintf(stderr, "=> (%s)\n", varname); // DEBUG
    ////////////////////
    free(varname);
    return EXIT_SUCCESS;
}

static int try_resolve_var(token_t *tok, size_t i, shell_t *shell)
{
    int ret = check_variable_name(&(tok->token[i + 1]));

    if (ret == EXIT_ERROR) {
        return EXIT_ERROR;
    } else if (ret == EXIT_SUCCESS) {
        if (process_subst(tok, (i + 1), shell) == EXIT_ERROR) {
            return EXIT_ERROR;
        }
    }
    return ret;
}

int try_subst_variable(token_t *tok, shell_t *shell)
{
    if (tok->id != ID_WITHOUT && tok->id != ID_DOUBLE_QUOTE) {
        return EXIT_SUCCESS;
    } else if (tok->token == NULL) {
        return EXIT_SUCCESS;
    }
    for (size_t i = 0; tok->token[i] != '\0'; i++) {
        if (tok->token[i] == '$'
            && try_resolve_var(tok, i, shell) == EXIT_ERROR) {
            return EXIT_ERROR;
        }
    }
    return EXIT_SUCCESS;
}
