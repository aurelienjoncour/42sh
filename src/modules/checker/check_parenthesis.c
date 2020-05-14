/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-07T17:06:50+02:00 | Author: simon
*/

#include "shell.h"

static const char *ERR_MISS_PARENTHESIS = "Too many %c's.\n";

bool check_parenthesis(cmd_t *cmd)
{
    size_t idx_last_char;

    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        idx_last_char = (strlen(ptr->token) - 1);
        if (ptr->id == ID_PARENTHESE && ptr->token[idx_last_char] != ')') {
            fprintf(stderr, ERR_MISS_PARENTHESIS, '(');
            return true;
        }
        if (my_str_have_char(ptr->token, ')') != -1 && ptr->type != D_DELIM) {
            fprintf(stderr, ERR_MISS_PARENTHESIS, ')');
            return true;
        }
    }
    return false;
}
