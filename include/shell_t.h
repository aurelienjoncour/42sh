/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** minishell header
*/

#ifndef H_SHELL_T
#define H_SHELL_T

#include "fd_t.h"

typedef struct minishell {
    env_t env;
    env_t local;
    //history_t *history;
    env_t alias;
    fd_t fd;
    char *prev_path;
    int exit_status;
    bool exit;
} shell_t;

#endif
