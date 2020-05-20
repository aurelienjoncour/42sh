/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-18T10:21:27+02:00 | Author: simon
*/

#include "shell.h"

static size_t *get_block_size(char *label, char *token, char *value,
size_t idx)
{
    size_t *bloc_size = malloc(sizeof(size_t) * 4);

    if (!bloc_size)
        return NULL;
    bloc_size[0] = (idx > 1) ? (idx - 1) : 0;
    bloc_size[1] = strlen(value);
    bloc_size[2] = strlen(label);
    if (token[idx] == '{') {
        bloc_size[3] = strlen(&token[bloc_size[0] + 2 + bloc_size[2] + 1]);
    } else {
        bloc_size[3] = strlen(&token[bloc_size[0] + 1 + bloc_size[2]]);
    }
    return bloc_size;
}

static char *fill_token(char *value, size_t idx, char *token,
char *label)
{
    size_t *bloc_size = get_block_size(label, token, value, idx);
    size_t size = bloc_size[0] + bloc_size[1] + bloc_size[3];
    char *ret = malloc(sizeof(char) * (size + 1));

    if (ret == NULL || !bloc_size) {
        return NULL;
    }
    ret[size] = '\0';
    if (bloc_size[0] > 0) {
        strncpy(ret, token, bloc_size[0]);
    }
    if (bloc_size[1] > 0)
        strcpy(&ret[bloc_size[0]], value);
    if (bloc_size[3] > 0) {
        strcpy(&ret[bloc_size[0] + bloc_size[1]],
            &token[strlen(token) - bloc_size[3]]);
    }
    free(bloc_size);
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
        value = my_strdup("");
        if (!value)
            return EXIT_ERROR;
    }
    ret = fill_token(value, idx, tok->token, label);
    if (ret == NULL)
        return EXIT_ERROR;
    free(tok->token);
    free(value);
    tok->token = ret;
    return EXIT_SUCCESS;
}
