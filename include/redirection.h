/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** header
*/

#ifndef H_REDIRECT
#define H_REDIRECT

#include "redirection_t.h"

// Tool function
bool is_redirect_type(redirect_t *redirect, REDIRECT_TYPE compare);
bool token_is_file_redirect(ID id);

// Sub functions
int redirection_open_file(redirect_t *redirect);

int do_redirection(redirect_t *redirect);
int redirect_stdin_to_command(redirect_t *redirect);

// MAIN FUNCTIONS
int redirection_process(cmd_t *cmd, redirect_t *ptr_redirect);
void clean_redirect(redirect_t *redirect, shell_t *shell);

#endif
