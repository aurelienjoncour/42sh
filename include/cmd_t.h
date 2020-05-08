/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
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
    // TODO
} cmd_t;


#endif
