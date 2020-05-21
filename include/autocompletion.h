/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** autocompletion header
*/

#ifndef AUTOCOMPLETION_H
#define AUTOCOMPLETION_H

#include "env_t.h"

typedef struct file_s
{
    char *name;
    struct file_s *next;
} file_t;

int check_tab(char **line, size_t *pos, int ch, env_t *env);
file_t *get_files(char *path, size_t pos, env_t *env);
int complete_line(char **line, file_t *files, size_t *pos, bool multi);

#endif