/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** Created: 2020-04-02T17:06:06+02:00 | Author: simon
*/

#ifndef H_FD_T
#define H_FD_T

typedef struct fd {
    int prev_pipein;
    int pipe_fd[2];
    int stdin;
    int stdout;
} fd_t;

#endif
