/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** variable environment : create and destroy
*/

#include "my.h"

void my_env_destroy(env_t *env)
{
    if (!env)
        return;
    for (int i = 0; i < env->size; i++) {
        free(env->var[i]);
        env->var[i] = NULL;
    }
    free(env->var);
    env->var = NULL;
    env->size = 0;
}

int my_env_create(env_t *env, char **copy_env)
{
    int size_env = word_array_len(copy_env);

    if (!env)
        return EXIT_ERROR;
    if (size_env == 0) {
        env->size = 0;
        env->var = NULL;
        return EXIT_SUCCESS;
    }
    env->var = my_env_alloc(copy_env, NULL, size_env, size_env);
    if (!env->var) {
        env->size = 0;
        env->var = NULL;
        return EXIT_ERROR;
    }
    env->size = size_env;
    return EXIT_SUCCESS;
}
