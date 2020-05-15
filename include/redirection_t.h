/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** header
*/

#ifndef H_REDIRECT_T
#define H_REDIRECT_T

typedef enum redirection_type {
    NO_REDIRECT = 0,
    R_LEFT = 2,
    R_DLEFT = 4,
    R_RIGHT = 8,
    R_DRIGHT = 16
} REDIRECT_TYPE;

#define REDIRECT_MASK 30

typedef struct redirection {
    int type;
    char *string_left;
    char *filename_right;
    int fd_left;
    int fd_right;
    int pipe_redirect[2];
} redirect_t;

#endif
