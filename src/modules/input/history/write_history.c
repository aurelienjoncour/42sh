/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "history_t.h"
#include "my.h"

void write_history(history_t *hist)
{
    size_t i;
    char tmp[3];

    if (!hist->history) {
        return;
    }
    i = (hist->size) ? hist->size : 0;
    for (; hist->history[i]; i++) {
        write(hist->fd, "#+", 2);
        sprintf(tmp, "%i", hist->date[i].hours);
        write(hist->fd, tmp, strlen(tmp));
        write(hist->fd, ":", 1);
        sprintf(tmp, "%i", hist->date[i].minutes);
        write(hist->fd, tmp, strlen(tmp));
        write(hist->fd, "\n", 1);
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

static void load_time(date_t *date)
{
    time_t clock = time(NULL);
    struct tm *time = localtime(&clock);


    date->hours = 0;
    date->minutes = 0;
    if (!time)
        return;
    date->hours = time->tm_hour;
    date->minutes = time->tm_min;
}

static bool add_time(history_t *hist)
{
    date_t *tmp;
    int i;
    int u;

    for (i = 0; hist->history && hist->history[i]; i++);
    tmp = malloc(sizeof(date_t) * (i + 1));
    if (!tmp)
        return false;
    for (u = 0; hist->history[u] && u < i; u++)
        tmp[u] = hist->date[u];
    load_time(&tmp[u]);
    free(hist->date);
    hist->date = tmp;
    return true;
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
        if (tab[y + 1] && tab[y + 1][0] != '\0')
            new_line[i++] = ' ';
        free(tab[y]);
    }
    free(tab);
    new_line[i] = '\0';
}

char **history_manage(history_t *hist, char *new_line)
{
    char **env = hist->history;
    size_t size = get_history_size(env);

    if ((size != 0 && my_strcmp(env[size - 1], new_line) == 0) ||
        new_line[0] == '\0')
        return env;
    clean_string(new_line);
    if (size > 0 && my_strcmp(env[size - 1], new_line) == 0)
        return env;
    if (!add_time(hist))
        return env;
    return add_to_hist(env, new_line);
}
