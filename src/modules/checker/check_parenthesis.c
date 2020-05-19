/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-07T17:06:50+02:00 | Author: simon
*/

#include "shell.h"

static const char *ERR_MISS_PARENTHESIS = "Too many %c's.\n";
static const char *ERR_BAD_PARENTHESIS = "Badly placed ()'s.\n";

static bool check_parenthesis_position(cmd_t *cmd)
{
    bool have_parenth = false;
    bool have_text = false;

    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (is_separator(ptr) && have_parenth == true && have_text == true) {
            break;
        }
        if (is_text_token(ptr, false) == true)
            have_text = true;
        if (is_separator(ptr) == true) {
            have_parenth = false;
            have_text = false;
        } else if (ptr->id == ID_PARENTHESE)
            have_parenth = true;
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

    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (is_separator(ptr) && count_parenth > 1) {
            break;
        }
        if (is_separator(ptr) == true) {
            count_parenth = 0;
        } else if (ptr->id == ID_PARENTHESE) {
            count_parenth++;
        }
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
