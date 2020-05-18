/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-18T10:21:27+02:00 | Author: simon
*/

#include "shell.h"

static bool is_text_token(token_t *token)
{
    if (!token) {
        return false;
    } else if (token->type == D_DELIM && token->id != ID_PARENTHESE) {
        return true;
    }
    if (token->id == ID_WITHOUT) {
        if (token->prev && is_redirection(token->prev->id) == true) {
            return false;
        }
        return true;
    }
    return false;
}

bool is_command_name(token_t *token)
{
    if (is_text_token(token) == false) {
        return false;
    }
    if (token->prev == NULL) {
        return true;
    }
    for (token_t *ptr = token->prev; ptr != NULL; ptr = ptr->prev) {
        if (ptr->type == D_SEPARATOR || ptr->id == ID_PIPE) {
            break;
        }
        if (is_text_token(ptr) == true) {
            return false;
        }
    }
    return true;
}

int try_subst_alias(token_t *tok, shell_t *shell)
{
    // TODO

    return EXIT_SUCCESS;
}
