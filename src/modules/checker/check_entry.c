/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-07T17:06:50+02:00 | Author: simon
*/

#include "shell.h"

static const char *ERR_MISSING_QUOTE = "Unmatched '%c'.\n";
static const char *ERR_MISSING_REDIR_NAME = "Missing name for redirect.\n";

static const char *QUOTES = "\"'`";

bool is_redirection(ID token_id)
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
