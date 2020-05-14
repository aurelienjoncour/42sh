/*
** EPITECH PROJECT, 2020
** parser
** File description:
** tokeniser
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_t.h"
#include "parser.h"

extern const parser_t DELIMIT[];

static int tokeniser_build(char *entry, size_t *cursor, token_t *start,
token_t **ptr_last)
{
    ID prev_id = ID_WITHOUT;
    ssize_t index = 0;

    while (entry[cursor[1]] != '\0') {
        index = is_special_id(entry, cursor);
        if (index != -1 && prev_id == ID_IGNORE) {
            prev_id = ID_WITHOUT;
            cursor[1] += strlen(DELIMIT[index].start);
            continue;
        }
        if (index == -1) {
            cursor[1]++;
        } else {
            *ptr_last = get_last_token(start);
            if (create_token((*ptr_last), entry, cursor, index) == EXIT_ERROR)
                return EXIT_ERROR;
            prev_id = DELIMIT[index].id;
        }
    }
    return EXIT_SUCCESS;
}

static void push_text_if_empty(token_t *start, token_t **ptr_last,
char *entry, size_t *cursor)
{
    if (start->token[0] == '\0' || !start->token) {
        (*ptr_last) = get_last_token(start);
        create_token((*ptr_last), entry, cursor, 0);
    }
}

token_t *tokeniser(char *entry)
{
    size_t cursor[2] = {0};
    size_t size;
    token_t *start = create_node("\0", ID_WITHOUT, D_NORMAL);
    token_t *last = NULL;
    token_t *data = NULL;

    if (start == NULL)
        return NULL;
    else if (tokeniser_build(entry, cursor, start, &last) == EXIT_ERROR)
        return NULL;
    push_text_if_empty(start, &last, entry, cursor);
    last = get_last_token(last);
    if (last && strlen(last->token)) {
        data = create_node("\0", 0, 0);
        add_node_at_the_end(last, data);
        last = get_last_token(last);
    }
    size = (cursor[1] - cursor[0] + 1);
    last->token = my_strncat_realloc(last->token, entry + cursor[0], size);
    return start;
}
