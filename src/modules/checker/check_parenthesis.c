/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-07T17:06:50+02:00 | Author: simon
*/

#include "shell.h"
static const char *ERR_MISS_PARENTHESIS = "Too many %c's.\n";
static const char *ERR_BAD_PARENTHESIS = "Badly placed ()'s.\n";

static const char *SCRIPT_TOKEN[] =
{
    "if",
    "elif",
    "foreach",
    NULL
};

static bool is_scripting_token(token_t *ptr)
{
    if (ptr->id != ID_WITHOUT) {
        return false;
    }
    for (size_t i = 0; SCRIPT_TOKEN[i] != NULL; i++) {
        if (strcmp(SCRIPT_TOKEN[i], ptr->token) == 0) {
            return true;
        }
    }
    return false;
}

static bool check_token(token_t *ptr, bool *have_text, bool *have_parenth,
bool *is_script)
{
    if ((is_separator(ptr) && *have_parenth == true && *have_text == true)) {
        return true;
    } else if (is_scripting_token(ptr) == true) {
        *is_script = true;
    }
    if (*is_script == false && is_text_token(ptr, false) == true)
        *have_text = true;
    if (is_separator(ptr) == true) {
        *have_parenth = false;
        *have_text = false;
        *is_script = false;
    } else if (ptr->id == ID_PARENTHESE) {
        *have_parenth = true;
    }
    if (ptr->id == ID_PARENTHESE && is_script == true) {
        while (ptr != NULL && is_separator(ptr) == false) {
            ptr = ptr->next;
        }
    }
    return false;
}

static bool check_parenthesis_position(cmd_t *cmd)
{
    bool have_parenth = false;
    bool have_text = false;
    bool is_script = false;

    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (check_token(ptr, &have_text, &have_parenth, &is_script)) {
            break;
        }
        if (ptr == NULL) {
            break;
        }
    }
    if (have_parenth == true && have_text == true) {
        my_putstr_error(ERR_BAD_PARENTHESIS);
        return true;
    }
    return false;
}

static bool check_parenthesis_serie(cmd_t *cmd)
{
    size_t count_parenth = 0;
    bool have_script = false;

    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (is_separator(ptr) && count_parenth > 1) {
            break;
        }
        if (is_scripting_token(ptr) == true)
            have_script = true;
        if (is_separator(ptr) == true) {
            count_parenth = 0;
            have_script = true;
        } else if (ptr->id == ID_PARENTHESE && !have_script)
            count_parenth++;
    }
    if (count_parenth > 1) {
        fprintf(stderr, ERR_MISS_PARENTHESIS, ')');
        return true;
    }
    return false;
}

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
    if (check_parenthesis_position(cmd) || check_parenthesis_serie(cmd)) {
        return true;
    }
    return false;
}
