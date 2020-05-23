/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-20T17:14:11+02:00 | Author: simon
*/

#include "my.h"

static const char *SPACE = "\t ";
static const char *SPECIAL = "&|<>();`\\'\"";

static const int TYPE_TEXT = 0;
static const int TYPE_SPACE = 1;
static const int TYPE_SPEC = 2;

static int get_type_char(char c)
{
    if (my_str_have_char(SPACE, c) != -1) {
        return TYPE_SPACE;
    } else if (my_str_have_char(SPECIAL, c) != -1) {
        return TYPE_SPEC;
    }
    return TYPE_TEXT;
}

static void shift_str(char *entry, ssize_t idx_beg, ssize_t size,
bool is_left)
{
    if (is_left) {
        for (ssize_t i = idx_beg; i < (idx_beg + size); i++) {
            entry[i] = entry[i + 1];
        }
    } else {
        for (ssize_t i = idx_beg; i >= (idx_beg - size); i--) {
            entry[i] = entry[i - 1];
        }
    }
}

static ssize_t check_move_quote(char *entry, ssize_t idx, bool is_left,
char quote)
{
    ssize_t size = 0;

    if ((is_left && get_type_char(entry[idx + 1]) != TYPE_TEXT) || (!is_left
        && idx > 0 && get_type_char(entry[idx - 1]) != TYPE_TEXT)) {
        return idx;
    }
    while (is_left && entry[size + idx + 1] != '\0'
        && get_type_char(entry[size + idx + 1]) == TYPE_TEXT) {
        size++;
    }
    while (!is_left && (idx - 1 - size) >= 0
        && get_type_char(entry[idx - 1 - size]) == TYPE_TEXT) {
        size++;
    }
    shift_str(entry, idx, size, is_left);
    if (is_left)
        entry[idx + size] = quote;
    else
        entry[idx - size] = quote;
    return (is_left) ? (idx + size) : (idx - size);
}

bool char_is_quote(char *entry, ssize_t idx)
{
    if (!(entry[idx] == '\'' || entry[idx] == '"')) {
        return false;
    }
    if (idx == 0) {
        return true;
    } else if (entry[idx - 1] != '\\') {
        return true;
    }
    return false;
}

int parser_move_quote(char *entry)
{
    char is_quote = 0;

    for (ssize_t i = 0; entry[i] != '\0'; i++) {
        if (is_quote == 0 && char_is_quote(entry, i)) {
            is_quote = entry[i];
        } else if (char_is_quote(entry, i) && is_quote == entry[i]) {
            is_quote = 0;
            i = check_move_quote(entry, i, true, entry[i]);
        }
    }
    is_quote = 0;
    for (ssize_t i = (my_strlen(entry) - 1); i >= 0; i--) {
        if (is_quote == 0 && char_is_quote(entry, i)) {
            is_quote = entry[i];
        } else if (char_is_quote(entry, i) && is_quote == entry[i]) {
            is_quote = 0;
            i = check_move_quote(entry, i, false, entry[i]);
        }
    }
    return EXIT_SUCCESS;
}
