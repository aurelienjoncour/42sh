/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** Created: 2020-03-26T11:24:12+01:00 | Author: simon
*/

#include "my.h"

int my_env_size(env_t *env)
{
    int len = 0;

    if (!env || !env->var || env->size == 0) {
        return 0;
    }
    for (ssize_t i = 0; i < env->size; i++) {
        if (env->var[i] != NULL) {
            len++;
        }
    }
    return len;
}
