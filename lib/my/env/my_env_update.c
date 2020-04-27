/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** variable environment : Update an entry
*/

#include "my.h"

int my_env_update(env_t *self, const char *label, const char *value)
{
    char **entry = my_env_get_ptr(self, label);
    int len_label = my_strlen(label);
    int len_value = my_strlen(value);

    if (!entry)
        return EXIT_ERROR;
    free(*entry);
    *entry = malloc(sizeof(char) * (len_value + len_label + 2));
    if (!(*entry)) {
        my_putstr_error("ERROR: malloc : set_variable\n");
        return EXIT_ERROR;
    }
    my_strcpy(*entry, label);
    (*entry)[len_label] = '=';
    if (value) {
        my_strcpy(*entry + len_label + 1, value);
    }
    (*entry)[len_value + len_label + 1] = '\0';
    return EXIT_SUCCESS;
}
