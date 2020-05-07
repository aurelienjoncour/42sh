/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** variable environment : realloc the environment
*/

#include "my.h"

static char **env_alloc(int size)
{
    char **new_env = malloc(sizeof(char *) * (size + 1));

    if (!new_env) {
        my_putstr_error("ERROR: env_alloc : malloc error\n");
        return NULL;
    }
    for (ssize_t i = 0; i <= size; i++) {
        new_env[i] = NULL;
    }
    return new_env;
}

static int env_dup(char **src, char **dest, int size_src, int idx_begin)
{
    int idx_dest = idx_begin;
    int max_size = (size_src + idx_begin);

    for (ssize_t i = 0; i < size_src; i++) {
        if (src[i] != NULL && idx_dest < max_size) {
            dest[idx_dest] = my_strdup(src[i]);
            idx_dest++;
        }
        if ((src[i] != NULL && idx_dest < max_size) && !dest[idx_dest - 1]) {
            my_putstr_error("ERROR: malloc error (env_dup)\n");
            return EXIT_ERROR;
        }
    }
    return EXIT_SUCCESS;
}

char **my_env_alloc(char **src, env_t *old, int new_size, int src_size)
{
    char **new_env = env_alloc(new_size);
    int ret;
    int curr_env_size = 0;

    if (!new_env || (new_size < src_size)) {
        return NULL;
    }
    if (old != NULL && old->var != NULL && old->size <= new_size) {
        ret = env_dup(old->var, new_env, old->size, 0);
        if (ret == EXIT_ERROR)
            return NULL;
        curr_env_size += old->size;
    }
    if (src != NULL && (curr_env_size + src_size) <= new_size) {
        ret = env_dup(src, new_env, src_size, curr_env_size);
        if (ret == EXIT_ERROR)
            return NULL;
    }
    return new_env;
}
