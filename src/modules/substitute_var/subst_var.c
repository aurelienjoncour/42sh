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
    if (strncmp(str, "?", 1) == 0 && !(char_is_letter(str[1])
            || (str[1] >= '0' && str[1] <= '9'))) {
        return EXIT_SUCCESS;
    } else if (strncmp(str, "{?}", 3) == 0) {
        return EXIT_SUCCESS;
    }
    if (char_is_letter(str[0]) || (str[0] >= '0' && str[0] <= '9')) {
        return EXIT_SUCCESS;
    } else if (str[0] == '{' && (char_is_letter(str[1])
        || (str[1] >= '0' && str[1] <= '9'))) {
        return EXIT_SUCCESS;
    }
    if (str[0] == ' ' || str[0] == '\t')
        return EXIT_FAIL;
    my_putstr_error(ERR_VAR_NAME);
    return EXIT_ERROR;
}

static char *get_varname(token_t *tok, size_t idx)
{
    size_t size = 0;
    char *ret = NULL;

    if (tok->token[idx] == '{') {
        idx++;
    }
    for (; tok->token[size + idx] != '\0'; size++) {
        if (!char_is_letter(tok->token[idx + size])
            && !(tok->token[idx + size] >= '0'
            && tok->token[idx + size] <= '9')
            && tok->token[idx + size] != '_'
            && tok->token[idx + size] != '?') {
            break;
        }
    }
    ret = my_strndup(&(tok->token[idx]), size);
    return ret;
}

static int process_subst(token_t *tok, size_t idx, shell_t *shell)
{
    char *varname = get_varname(tok, idx);
    int exit_val = subst_exit_status(tok, idx, shell, varname);
    int ret[2];

    if (exit_val == EXIT_ERROR)
        return EXIT_ERROR;
    else if (exit_val == EXIT_SUCCESS)
        return EXIT_SUCCESS;
    ret[0] = process_subst_value(varname, tok, &shell->env, idx);
    ret[1] = process_subst_value(varname, tok, &shell->local, idx);
    if (ret[0] == EXIT_ERROR || ret[1] == EXIT_ERROR) {
        return EXIT_ERROR;
    } else if (ret[0] == EXIT_FAIL && ret[1] == EXIT_FAIL) {
        ret[0] = subst_undefined_argv(varname, tok, idx);
        if (ret[0] != EXIT_FAIL)
            return ret[0];
        return subst_exit_error(varname);
    }
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
        if (tok->token[i] == '\0') {
            break;
        }
    }
    return EXIT_SUCCESS;
}
