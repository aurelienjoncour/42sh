/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include <unistd.h>
#include <string.h>
#include "history_t.h"
#include "my.h"

void write_history(history_t *hist)
{
    size_t i = (hist->size) ? hist->size : 0;

    for (; hist->history[i]; i++) {
        write(hist->fd, hist->history[i], strlen(hist->history[i]));
        write(hist->fd, "\n", 1);
    }
}

static char **add_to_hist(char **env, char *new_line)
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

static void clean_string(char *new_line)
{
    size_t i = 0;
    char **tab = my_str_to_word_array(new_line, "\t \n");

    if (!tab)
        return;
    for (size_t y = 0; tab[y]; y++) {
        for (size_t x = 0; tab[y][x]; x++) {
            new_line[i] = tab[y][x];
            i++;
        }
        if (tab[y + 1] && tab[y][0] != '\0')
            new_line[i++] = ' ';
        free(tab[y]);
    }
    free(tab);
    new_line[i] = '\0';
}

char **history_manage(char **env, char *new_line)
{
    size_t size = get_history_size(env);

    if ((size != 0 && my_strcmp(env[size - 1], new_line) == 0) ||
        new_line[0] == '\0')
        return env;
    clean_string(new_line);
    if (size > 0 && my_strcmp(env[size - 1], new_line) == 0)
        return env;
    return add_to_hist(env, new_line);
}