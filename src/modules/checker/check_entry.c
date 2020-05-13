/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-07T17:06:50+02:00 | Author: simon
*/

#include "shell.h"

static const char *ERR_MISSING_QUOTE = "Unmatched '%c'.\n";
static const char *ERR_MISSING_REDIR_NAME = "Missing name for redirect.\n";
static const char *ERR_SEVERAL_REDIR_OUT = "Ambiguous output redirect.\n";
static const char *ERR_SEVERAL_REDIR_IN = "Ambiguous input redirect.\n";
static const char *ERR_NULL_CMD = "Invalid null command.\n";

static const char *QUOTES = "\"'`";

static bool str_is_word(const char *str)
{
    // if (str == NULL)
    //     return false;
    // for (size_t i = 0; REDIR_PATT[i] != NULL; i++) {
    //     if (my_strcmp(str, REDIR_PATT[i]) == 0) {
    //         return false;
    //     }
    // }
    return true;
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
        if (ptr->id != ID_REDIRECTION && ptr->id != ID_DOUBLE_RIGHT
            && ptr->id != ID_RIGHT && ptr->id != ID_DOUBLE_LEFTT
            && ptr->id != ID_LEFT) {
            continue;
        }
        if (ptr->next == NULL || ptr->next->id != ID_WIHOUT) {
            my_putstr_error(ERR_MISSING_REDIR_NAME);
            return true;
        }
    }
    return false;
}

bool have_several_redirection(cmd_t *cmd)
{
    int serie;
    int occur;
    bool err = false;

    my_str_count_char_suite(cmd->command, '<', &occur, &serie);
    if (occur > 2 || (occur == 2 && serie != 2)) {
        my_putstr_error(ERR_SEVERAL_REDIR_IN);
        err = true;
    }
    my_str_count_char_suite(cmd->command, '>', &occur, &serie);
    if (occur > 2 || (occur == 2 && serie != 2)) {
        my_putstr_error(ERR_SEVERAL_REDIR_OUT);
        err = true;
    }
    if (err == true) {
        return true;
    }
    return false;
}

bool have_null_command(cmd_t *cmd)
{
    // int len = word_array_len(cmd->wa);
    // bool have_redirection_alpha = false;
    // bool have_redirection_beta = false;
    //
    // if (len != 4 && len != 2) {
    //     return false;
    // }
    // for (size_t j = 0; REDIR_PATT[j] != NULL; j++) {
    //     if (my_strcmp(REDIR_PATT[j], cmd->wa[0]) == 0) {
    //         have_redirection_alpha = true;
    //     }
    //     if (len == 4 && my_strcmp(REDIR_PATT[j], cmd->wa[2]) == 0) {
    //         have_redirection_beta = true;
    //     }
    // }
    // if (have_redirection_alpha && (len != 4 || have_redirection_beta)) {
    //     my_putstr_error(ERR_NULL_CMD);
    //     return true;
    // }
    return false;
}
