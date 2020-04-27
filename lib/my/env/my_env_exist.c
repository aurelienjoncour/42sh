/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** Created: 2020-03-27T09:45:09+01:00 | Author: simon
*/

#include "my.h"

bool my_env_exist(env_t *env, const char *label)
{
    char *entry;

    if (!env || !label) {
        return false;
    }
    entry = my_env_get(env, label);
    if (entry == NULL) {
        return false;
    } else {
        return true;
    }
}
