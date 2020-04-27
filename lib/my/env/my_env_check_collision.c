/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** Created: 2020-03-27T09:55:56+01:00 | Author: simon
*/

#include "my.h"

// Check if two environment array have variable label conflicts

static bool my_env_line_cmp(const char *linea, const char *lineb)
{
    if (!linea || !lineb) {
        return false;
    }
    for (size_t i = 0; linea[i] != '\0' && lineb[i] != '\0'; i++) {
        if (linea[i] == '=' && lineb[i] == '=') {
            return true;
        } else if (linea[i] != lineb[i]) {
            return false;
        }
    }
    return false;
}

int my_env_check_collision(const env_t *env, char **env_array)
{
    if (!env || !env_array)
        return -1;
    for (size_t i = 0; env_array[i] != NULL; i++) {
        for (size_t j = 0; env_array[j] != NULL; j++) {
            if (i == j)
                continue;
            else if (my_env_line_cmp(env_array[i], env_array[j]))
                return (int)i;
        }
    }
    if (!env->var)
        return -1;
    for (size_t i = 0; env->var[i] != NULL; i++) {
        for (size_t j = 0; env_array[j] != NULL; j++) {
            if (my_env_line_cmp(env->var[i], env_array[j])) {
                return (int)j;
            }
        }
    }
    return -1;
}
