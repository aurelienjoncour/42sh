/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** Created: 2020-04-06T08:23:05+02:00 | Author: simon
*/

#include "shell.h"

static const int STATE_IGN_CHAR = 0;
static const int STATE_ADD_CHAR = 1;
static const int STATE_DEL_CHAR = 2;

extern const char BREAK;

extern const int TYPE_WORD;
extern const int TYPE_REDIR;
extern const int TYPE_SPACE;
extern const int TYPE_BACK;
extern const int TYPE_DELIM_A;
extern const int TYPE_DELIM_B;

// => remove serveral spaces (not in text block) : [echo hello "w  orld"]
// => add BREAK between redirection (<,<<,>>,>) : [echo h > log]

static int get_action(const int prev_type_char, const int type_char,
const int delim)
{
    if (type_char == TYPE_REDIR && prev_type_char != TYPE_SPACE
            && prev_type_char != TYPE_REDIR) {
        return STATE_ADD_CHAR;
    } else if (prev_type_char == TYPE_REDIR && type_char != TYPE_SPACE
            && type_char != TYPE_REDIR) {
        return STATE_ADD_CHAR;
    }
    if (delim == -1 && type_char == TYPE_SPACE) {
        return STATE_DEL_CHAR;
    }
    return STATE_IGN_CHAR;
}

static size_t get_length_formatted(const char *command)
{
    size_t len = 0;
    int type_char = -1;
    int prev_type_char = -1;
    int action;
    int delim = -1;

    for (size_t i = 0; command[i] != '\0'; i++) {
        type_char = get_type_char(command[i], delim);
        if (set_delim_mode(type_char, prev_type_char, &delim)) {
            continue;
        }
        action = get_action(prev_type_char, type_char, delim);
        if (action == STATE_ADD_CHAR) {
            len++;
        }
        len++;
        prev_type_char = type_char;
    }
    return len;
}

static void fill_formatted_command(char *dest, const char *src, size_t len)
{
    size_t idx_dest = 0;
    int type_char = -1;
    int prev_type_char = -1;
    int action;
    int delim = -1;

    dest[len] = '\0';
    for (size_t i = 0; src[i] != '\0' && idx_dest < len; i++) {
        type_char = get_type_char(src[i], delim);
        if (set_delim_mode(type_char, prev_type_char, &delim))
            continue;
        action = get_action(prev_type_char, type_char, delim);
        prev_type_char = type_char;
        if (action == STATE_ADD_CHAR || action == STATE_DEL_CHAR)
            dest[idx_dest++] = BREAK;
        if (action == STATE_DEL_CHAR) {
            continue;
        }
        dest[idx_dest++] = src[i];
    }
}

char *command_format(const char *command)
{
    size_t len = get_length_formatted(command);
    char *ret = NULL;

    if (len == 0) {
        return NULL;
    }
    ret = malloc(sizeof(char) * (len + 1));
    if (!ret)
        return NULL;
    fill_formatted_command(ret, command, len);
    return ret;
}
