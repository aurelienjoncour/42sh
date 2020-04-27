/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** minishell header
*/

#ifndef H_MINISHELL_T
#define H_MINISHELL_T

#include "fd_t.h"

typedef struct minishell {
    env_t env;
    char *prev_path;
    int exit_status;
    bool exit;
    fd_t fd;
} minishell_t;

#endif
