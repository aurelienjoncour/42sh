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

static void shift_str_left(char *entry, size_t idx_beg, size_t size)
{
    for (size_t i = idx_beg; i < (idx_beg + size); i++) {
        entry[i] = entry[i + 1];
    }
}

static void check_move_quote(char *entry, size_t idx)
{
    size_t size = 0;
    char quote = entry[idx];

    if (get_type_char(entry[idx + 1]) != TYPE_TEXT) {
        return;
    }
    while (entry[size + idx + 1] != '\0'
        && get_type_char(entry[size + idx + 1]) == TYPE_TEXT) {
        size++;
    }
    shift_str_left(entry, idx, size);
    entry[idx + size] = quote;
}

static bool char_is_quote(char *entry, size_t idx)
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

    for (size_t i = 0; entry[i] != '\0'; i++) {
        if (is_quote == 0 && char_is_quote(entry, i)) {
            is_quote = entry[i];
        } else if (char_is_quote(entry, i) && is_quote == entry[i]) {
            is_quote = 0;
            check_move_quote(entry, i);
        }
    }
    return EXIT_SUCCESS;
}
