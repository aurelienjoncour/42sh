/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** minishell header
*/

#ifndef H_SHELL_T
#define H_SHELL_T

#include "fd_t.h"

typedef struct minishell {
    env_t env;
    char *prev_path;
    int exit_status;
    bool exit;
    fd_t fd;
} shell_t;

#endif
