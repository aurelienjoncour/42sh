/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** autocompletion header
*/

#ifndef AUTOCOMPLETION_H
#define AUTOCOMPLETION_H

#include "env_t.h"

int check_tab(char **line, size_t *pos, int ch, env_t *env);
file_list_t *get_files(char *path, size_t pos, env_t *env);
int complete_line(char **line, file_list_t *files, size_t *pos, bool multi);

#endif