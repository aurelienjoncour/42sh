/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** variable environment
*/

#include "my.h"

static void get_idx_symbol_and_length(char *env_var, int *len,
int *idx_symbol)
{
    for (int i = 0; env_var[i] != '\0'; i++) {
        if (env_var[i] == '=') {
            *idx_symbol = i;
            break;
        }
        (*len)++;
    }
    if (*idx_symbol == -1) {
        *idx_symbol = my_strlen(env_var) - 1;
    }
}

char *my_env_get_var_label(char *entry)
{
    int len = 0;
    int idx_symbol = -1;

    if (!entry)
        return NULL;
    get_idx_symbol_and_length(entry, &len, &idx_symbol);
    if (len == 0) {
        return NULL;
    }
    return my_strndup(entry, idx_symbol);
}
