/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** variable environment
*/

#include "my.h"

char *my_env_get_var_value(char *entry)
{
    int first_symb = 0;

    if (!entry)
        return NULL;
    for (size_t i = 0; entry[i] != '\0'; i++) {
        if (!first_symb && entry[i] == '=') {
            first_symb = 1;
        } else if (first_symb) {
            return my_strdup(&(entry[i]));
        }
    }
    return NULL;
}

char *my_env_get_value(env_t *env, const char *label)
{
    char *entry = my_env_get(env, label);

    if (!entry)
        return NULL;
    return my_env_get_var_value(entry);
}

int my_env_get_value_int(env_t *env, const char *label, bool *error)
{
    char *entry = my_env_get(env, label);
    char *value;
    int nbr;

    if (!entry) {
        if (error)
            *error = true;
        return 0;
    }
    value = my_env_get_var_value(entry);
    if (!value) {
        if (error)
            *error = true;
        return 0;
    }
    nbr = my_getnbr(value);
    free(value);
    if (error)
        *error = *error | false;
    return nbr;
}

double my_env_get_value_dec(env_t *env, const char *label, bool *error)
{
    char *entry = my_env_get(env, label);
    char *value;
    double nbr;

    if (!entry) {
        if (error)
            *error = true;
        return 0.0f;
    }
    value = my_env_get_var_value(entry);
    if (!value) {
        if (error)
            *error = true;
        return 0.0f;
    }
    nbr = my_get_double(value);
    free(value);
    if (error)
        *error = *error | false;
    return nbr;
}
