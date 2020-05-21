/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** minishell main function
*/

#include "shell.h"

char *get_env_entry(env_t *env, char *label)
{
    char *entry = NULL;

    if (!env || !env->var)
        return "";
    for (size_t i = 0; env->var[i]; i++) {
        if (my_strncmp(env->var[i], label, my_strlen(label)) == 0) {
            entry = malloc(sizeof(char) * (my_strlen(env->var[i]) - 6));
            if (!entry)
                return "";
            entry[0] = '\0';
            entry = my_strcat(entry, &env->var[i][7]);
            return entry;
        }
    }
    return "";
}
