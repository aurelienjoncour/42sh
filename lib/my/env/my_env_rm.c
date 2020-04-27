/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** variable environment : remove an entry
*/

#include "my.h"

int my_env_rm(env_t *env, const char *label)
{
    char **ptr = my_env_get_ptr(env, label);

    if (ptr == NULL || !env || !label) {
        return EXIT_FAILURE;
    }
    free(*ptr);
    *ptr = NULL;
    return EXIT_SUCCESS;
}
