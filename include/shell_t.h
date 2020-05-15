/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** minishell header
*/

#ifndef H_SHELL_T
#define H_SHELL_T

#include "fd_t.h"
#include "history_t.h"
#include "history_builtin.h"

typedef struct minishell {
    env_t env;
    env_t local;
    //history_t *history;
    // alias array
    fd_t fd;
    char *prev_path;
    int exit_status;
    bool exit;
    history_t history;
} shell_t;

#endif
