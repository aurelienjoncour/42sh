/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** Created: 2020-03-26T09:51:13+01:00 | Author: simon
*/

#include "my.h"

int my_env_merge(env_t *env, char **env_src)
{
    int size_env_src = word_array_len(env_src);
    int new_size;
    char **new_env = NULL;

    if (!env || !env_src) {
        return EXIT_ERROR;
    }
    if (my_env_check_collision(env, env_src) != -1) {
        return EXIT_FAILURE;
    }
    new_size = env->size + size_env_src;
    new_env = my_env_alloc(env_src, env, new_size, size_env_src);
    if (!new_env)
        return my_puterror("my_env_merge : alloc error", EXIT_ERROR);
    my_env_destroy(env);
    env->var = new_env;
    env->size = new_size;
    return EXIT_SUCCESS;
}
