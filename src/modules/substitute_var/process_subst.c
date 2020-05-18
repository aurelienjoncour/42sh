/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-18T10:21:27+02:00 | Author: simon
*/

#include "shell.h"

static char *fill_token(char *value, size_t idx, char *token,
char *label)
{
    size_t first_bloc_size = (idx > 1) ? (idx - 1) : 0;
    size_t size = first_bloc_size + strlen(&token[idx + strlen(label)])
        + strlen(value);
    char *ret = malloc(sizeof(char) * (size + 1));

    if (ret == NULL) {
        return NULL;
    }
    ret[size] = '\0';
    if (idx > 1) {
        strncpy(ret, token, (idx - 1));
    } else {
        first_bloc_size = 0;
    }
    strcpy(&ret[first_bloc_size], value);
    if (strlen(token + idx + strlen(label)) > 0) {
        strcpy(ret + first_bloc_size + strlen(value),
            &token[idx + strlen(label)]);
    }
    return ret;
}

int process_subst_value(char *label, token_t *tok, env_t *var, size_t idx)
{
    char *value;
    char *ret;

    if (my_env_exist(var, label) == false) {
        return EXIT_FAIL;
    }
    value = my_env_get_value(var, label);
    if (value == NULL) {
        return puterr("Var substitute : subst fail\n", EXIT_ERROR);
    }
    ret = fill_token(value, idx, tok->token, label);
    if (ret == NULL)
        return EXIT_ERROR;
    free(tok->token);
    free(value);
    tok->token = ret;
    return EXIT_SUCCESS;
}
