/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-07T17:06:50+02:00 | Author: simon
*/

#include "shell.h"

static const char *ERR_NULL_CMD = "Invalid null command.\n";

static bool check_null_parenthesis_token(token_t *ptr, size_t *count)
{
    if (ptr->type == D_SEPARATOR || ptr->id == ID_PIPE) {
        if (*count == 0) {
            return true;
        }
        *count = 0;
    } else if ((ptr->id == ID_WITHOUT
            && (!ptr->prev || !is_redirection(ptr->prev->id)))
            || (ptr->type == D_DELIM && ptr->id != ID_PARENTHESE)) {
        (*count)++;
    }
    return false;
}

static bool check_null_parenthesis(char *token)
{
    cmd_t *content;
    size_t count = 0;

    token[0] = ' ';
    token[strlen(token) - 1] = ' ';
    content = parse_entry(token);
    if (!content) {
        return true;
    }
    for (token_t *ptr = content->begin; ptr != NULL; ptr = ptr->next) {
        if (check_null_parenthesis_token(ptr, &count)) {
            return true;
        }
    }
    if (count == 0) {
        return true;
    }
    cmd_destroy(content);
    return false;
}

static bool process_check_parenthesis(token_t *ptr)
{
    char *dup;

    dup = my_strdup(ptr->token);
    if (!dup)
        return false;
    if (check_null_parenthesis(dup) == true)
        return true;
    free(dup);
    return false;
}

static bool check_null_cmd_token(size_t *count_text, token_t *ptr,
size_t *count_second_token)
{
    if (ptr->id == ID_PARENTHESE) {
        if (process_check_parenthesis(ptr) == true) {
            return true;
        }
    }
    if (ptr->id == ID_OR || ptr->id == ID_PIPE) {
        if (*count_text == 0) {
            return true;
        }
        *count_text = 0;
    } else if ((ptr->id == ID_WITHOUT
            && (!ptr->prev || !is_redirection(ptr->prev->id)))
            || (ptr->type == D_DELIM && ptr->id != ID_PARENTHESE)) {
        (*count_text)++;
    } else if (ptr->type != D_SEPARATOR && ptr->id != ID_PARENTHESE &&
            ptr->id != ID_BACKGROUND) {
        (*count_second_token)++;
    }
    return false;
}

bool have_null_command(cmd_t *cmd)
{
    size_t count_text = 0;
    size_t count_second_token = 0;

    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (check_null_cmd_token(&count_text, ptr, &count_second_token)) {
            my_putstr_error(ERR_NULL_CMD);
            return true;
        }
    }
    if (count_second_token != 0 && count_text == 0) {
        my_putstr_error(ERR_NULL_CMD);
        return true;
    }
    return false;
}
