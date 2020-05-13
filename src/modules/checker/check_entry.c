/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-07T17:06:50+02:00 | Author: simon
*/

#include "shell.h"

static const char *ERR_MISSING_QUOTE = "Unmatched '%c'.\n";
static const char *ERR_MISSING_REDIR_NAME = "Missing name for redirect.\n";
static const char *ERR_NULL_CMD = "Invalid null command.\n";

static const char *QUOTES = "\"'`";

static bool is_redirection(ID token_id)
{
    if (token_id == ID_DOUBLE_RIGHT || token_id == ID_RIGHT
        || token_id == ID_DOUBLE_LEFT || token_id == ID_LEFT) {
        return true;
    }
    return false;
}

bool have_missing_str_quote(const char *entry)
{
    char quote = 0;

    for (size_t i = 0; entry[i] != '\0'; i++) {
        if (my_str_have_char(QUOTES, entry[i]) == -1) {
            continue;
        }
        if (quote == 0) {
            quote = entry[i];
        } else if (quote == entry[i]) {
            quote = 0;
        }
    }
    if (quote != 0) {
        fprintf(stderr, ERR_MISSING_QUOTE, quote);
        return true;
    }
    return false;
}

bool have_missing_name_redirection(cmd_t *cmd)
{
    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (is_redirection(ptr->id) == false) {
            continue;
        }
        if (ptr->next == NULL || ptr->next->id != ID_WITHOUT) {
            my_putstr_error(ERR_MISSING_REDIR_NAME);
            return true;
        }
    }
    return false;
}

static bool have_null_command_check_token(bool *have_text, token_t *ptr,
token_t *prev_ptr)
{
    if (ptr->type == D_SEPARATOR || ptr->id == ID_PIPE) {
        if (*have_text == false
                && !(ptr->id == ID_SEP && prev_ptr->id == ID_SEP)) {
            return true;
        }
        *have_text = false;
    } else if ((ptr->id == ID_WITHOUT
            && (!prev_ptr || !is_redirection(prev_ptr->id)))
            || (ptr->type == D_DELIM && ptr->id != ID_PARENTHESE)) {
        *have_text = true;
    }
    return false;
}

bool have_null_command(cmd_t *cmd)
{
    bool have_text = false;
    token_t *prev_ptr = NULL;

    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (have_null_command_check_token(&have_text, ptr, prev_ptr)) {
            my_putstr_error(ERR_NULL_CMD);
            return true;
        }
        prev_ptr = ptr;
    }
    return false;
}
