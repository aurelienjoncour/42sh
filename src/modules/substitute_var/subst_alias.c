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

static void insert_new_token(token_t *old, cmd_t *new, cmd_t *main_cmd)
{
    token_t *prev = old->prev;
    token_t *post = old->next;

    if (prev != NULL) {
        prev->next = new->begin;
    } else {
        main_cmd->begin = new->begin;
    }
    if (post != NULL) {
        post->prev = new->end;
    } else {
        main_cmd->end = new->end;
    }
}

static char *format_value(char *value)
{
    char *ret = NULL;

    if (value == NULL) {
        return NULL;
    } else if (value[0] != '(') {
        return value;
    }
    ret = my_strndup(value + 1, my_strlen(value) - 2);
    free(value);
    return ret;
}

int try_subst_alias(cmd_t *cmd, token_t *tok, shell_t *shell)
{
    char *value = my_env_get_value(&shell->alias, tok->token);
    cmd_t *sub_cmd;

    value = format_value(value);
    if (!value) {
        return EXIT_SUCCESS;
    }
    sub_cmd = parse_entry(value);
    if (!sub_cmd || !sub_cmd->begin) {
        return puterr("Var subst: parse_entry : fail\n", EXIT_ERROR);
    }
    insert_new_token(tok, sub_cmd, cmd);
    cmd->size += (sub_cmd->size - 1);
    free(tok->token);
    free(tok);
    free(value);
    free(sub_cmd);
    return EXIT_SUCCESS;
}
