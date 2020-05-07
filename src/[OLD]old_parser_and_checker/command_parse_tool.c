/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-06T18:29:56+02:00 | Author: simon
*/

#include "shell.h"

static const char *CHAR_SPACE = " \t";
static const char *CHAR_DELIM = "\"'";
static const char *CHAR_REDIRECT = "<>";

static const char BACK = '\\';
const char BREAK = '\a';

const int TYPE_WORD = 0;
const int TYPE_REDIR = 1;
const int TYPE_SPACE = 2;
const int TYPE_BACK = 3;
const int TYPE_DELIM_A = 4;
const int TYPE_DELIM_B = 5;

int get_type_char(const char c, const int delim)
{
    if (c == BACK) {
        return TYPE_BACK;
    }
    if (delim == -1 && my_str_have_char(CHAR_SPACE, c) != -1) {
        return TYPE_SPACE;
    } else if (delim == -1 && my_str_have_char(CHAR_REDIRECT, c) != -1) {
        return TYPE_REDIR;
    }
    if (c == CHAR_DELIM[0]) {
        return TYPE_DELIM_A;
    } else if (c == CHAR_DELIM[1]) {
        return TYPE_DELIM_B;
    }
    return TYPE_WORD;
}

bool set_delim_mode(const int type_char, const int prev_type_char, int *delim)
{
    if (type_char == TYPE_DELIM_B || type_char == TYPE_DELIM_A) {
        if (prev_type_char == TYPE_BACK) {
            return false;
        }
        if (*delim == -1) {
            *delim = type_char;
            return true;
        } else if (*delim == type_char) {
            *delim = -1;
            return true;
        }
    }
    return false;
}
