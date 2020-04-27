/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** Created: 2020-04-03T10:50:19+02:00 | Author: simon
*/

#ifndef H_CMD_T
#define H_CMD_T

enum redirect_mode_in {
    FROM_STDIN = 0,
    FROM_IN = 1,
    NO_IN_REDIRECT
};

typedef enum redirect_mode_out {
    TO_OUT_ADD = 0,
    TO_OUT = 1,
    NO_OUT_REDIRECT
} redirect_mode_out_t;

typedef struct cmd {
    char *command;
    char *formatted;
    char **wa;
    char **cmd;
    char **redirect_in;
    char **redirect_out;
    bool err;
    enum redirect_mode_in red_mode_in;
    enum redirect_mode_out red_mode_out;
    int file_fd_in;
    int file_fd_out;
    int pipe_redirect[2];
} cmd_t;


#endif
