/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** variable environment : get an entry
*/

#include "my.h"

char *my_env_get(env_t *self, const char *label)
{
    int len_label = my_strlen(label);
    char *ptr_begin_entry = NULL;

    if (!self || !label)
        return NULL;
    for (int i = 0; i < self->size; i++) {
        if (!self->var[i])
            continue;
        ptr_begin_entry = &(self->var[i][0]);
        if (my_strstr(self->var[i], label) == ptr_begin_entry
                && my_strlen(self->var[i]) >= len_label
                && self->var[i][len_label] == '=') {
            return self->var[i];
        }
    }
    return NULL;
}

char **my_env_get_ptr(env_t *self, const char *label)
{
    int len_label = my_strlen(label);
    char *ptr_begin_entry = NULL;

    if (!self || !label)
        return NULL;
    for (int i = 0; i < self->size; i++) {
        if (!self->var[i])
            continue;
        ptr_begin_entry = &(self->var[i][0]);
        if (my_strstr(self->var[i], label) == ptr_begin_entry
                && my_strlen(self->var[i]) >= len_label
                && self->var[i][len_label] == '=') {
            return &(self->var[i]);
        }
    }
    return NULL;
}
