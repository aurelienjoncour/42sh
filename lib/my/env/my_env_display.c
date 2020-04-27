/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** variable environment : display content
*/

#include "my.h"

void my_env_display(env_t *env)
{
    if (!env) {
        my_putstr_error("my_env_display : NULL env_t\n");
        return;
    }
    for (int i = 0; i < env->size; i++) {
        if (env->var[i] == NULL)
            continue;
        my_putstr(env->var[i]);
        my_putchar('\n');
    }
}
