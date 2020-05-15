/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my_key.h"

#ifndef HIST_H
#define HIST_H

#define MAX_LINE 1000

typedef struct date_s
{
    int hours;
    int minutes;
} date_t;

typedef struct history_s
{
    int fd;
    char **history;
    date_t *date;
    size_t size;
    size_t pos;
} history_t;

char **read_file(int const fd);
void destroy_file(char **file);
bool init_history(history_t *hist);
void destroy_history(history_t *hist);
void write_history(history_t *hist);
char **history_manage(history_t *hist, char *new_line);
void rm_char(char *line, size_t *pos, bool stat);
void save_in_hist(char **line, history_t *hist);
char *add_char(char *str, char c, size_t pos);
size_t get_history_size(char **hist);
void history_build(history_t *hist);
bool init_input(void);
int my_getch(void);

#endif

