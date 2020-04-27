/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** variable environment : add new entry
*/

#include "my.h"

static int env_set_entry(env_t *self, const char *label, const char *value)
{
    int len_label = my_strlen(label);
    int len_entry = len_label + my_strlen(value) + 2;

    self->var[self->size - 1] = malloc(sizeof(char) * len_entry);
    if (!self->var[self->size - 1]) {
        my_puterror("ERROR: malloc error (env_set_entry)\n", EXIT_ERROR);
    }
    my_strcpy(self->var[self->size - 1], label);
    self->var[self->size - 1][len_label] = '=';
    my_strcpy(self->var[self->size - 1] + (len_label + 1), value);
    self->var[self->size - 1][len_entry - 1] = '\0';
    return EXIT_SUCCESS;
}

int my_env_add(env_t *self, const char *label, const char *value)
{
    char *entry;
    char **new_env;
    int size = self->size;

    if (!self)
        return EXIT_ERROR;
    entry = my_env_get(self, label);
    if (entry != NULL) {
        return my_puterror("my_env_add : label already exist\n", 0);
    }
    new_env = my_env_alloc(self->var, NULL, self->size + 1, self->size);
    if (!new_env)
        return EXIT_ERROR;
    my_env_destroy(self);
    self->var = new_env;
    self->size = (size + 1);
    if (env_set_entry(self, label, value))
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
