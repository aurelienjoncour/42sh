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
    char *label = NULL;

    if (!entry)
        return NULL;
    get_idx_symbol_and_length(entry, &len, &idx_symbol);
    if (len == 0) {
        return NULL;
    }
    label = malloc(sizeof(char) * len);
    if (!label) {
        my_putstr_error("Error: malloc (get_env_var_label)\n");
        return NULL;
    }
    my_strncpy(label, entry, idx_symbol + 1);
    label[idx_symbol + 1] = '\0';
    return label;
}
