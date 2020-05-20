/*
** EPITECH PROJECT, 2019
** 46sh
** File description:
** 47sh
*/

#include "shell.h"

char **add_to_hist(char **env, char *new_line)
{
    char **tab;
    int i;
    int u;

    for (i = 0; env && env[i]; i++);
    tab = malloc(sizeof(char *) * (i + 2));
    if (!tab)
        return NULL;
    for (u = 0; env[u] && u < i; u++) {
        tab[u] = my_strdup(env[u]);
        if (!tab[u])
            return NULL;
    }
    tab[u] = my_strdup(new_line);
    if (!tab[u])
        return NULL;
    tab[u + 1] = NULL;
    for (size_t y = 0; env[y]; free(env[y]), y++);
    free(env);
    return tab;
}