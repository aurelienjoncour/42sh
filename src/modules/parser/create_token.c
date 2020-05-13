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

static void first_block(token_t **ptr_data, token_t **ptr_last, char *argv,
size_t *cursor)
{
    size_t size;

    if (cursor[0] != cursor[1]) {
        if (strlen((*ptr_last)->token)) {
            (*ptr_data) = create_node("\0", 0, 0);
            add_node_at_the_end((*ptr_last), (*ptr_data));
        }
        (*ptr_last) = get_last_token((*ptr_last));
        size = (cursor[1] - cursor[0]);
        (*ptr_last)->token = my_strncat_realloc((*ptr_last)->token,
                                                (argv + cursor[0]), size);
        cursor[0] = cursor[1];
        (*ptr_data) = create_node("\0", 0, 0);
        add_node_at_the_end((*ptr_last), (*ptr_data));
    }
}

static void last_block(token_t **ptr_data, token_t **ptr_last, size_t *cursor,
ssize_t index)
{
    size_t len_delimit;

    if (strlen((*ptr_last)->token)) {
        (*ptr_data) = create_node("\0", 0, 0);
        add_node_at_the_end((*ptr_last), (*ptr_data));
    }
    (*ptr_last) = get_last_token((*ptr_last));
    len_delimit = strlen(DELIMIT[index].start);
    (*ptr_last)->token = my_strncat_realloc((*ptr_last)->token,
                                        DELIMIT[index].start, len_delimit);
    (*ptr_last)->id = DELIMIT[index].id;
    (*ptr_last)->type = DELIMIT[index].type;
    cursor[1] += strlen(DELIMIT[index].start);
    cursor[0] = cursor[1];
    (*ptr_data) = create_node("\0", 0, 0);
    add_node_at_the_end((*ptr_last), (*ptr_data));
}

static void middle_block(token_t **ptr_last, char *argv, size_t *cursor,
ssize_t index)
{
    token_t *data;
    size_t size;

    if (strlen((*ptr_last)->token)) {
        data = create_node("\0", 0, 0);
        add_node_at_the_end((*ptr_last), data);
    }
    (*ptr_last) = get_last_token((*ptr_last));
    size = (cursor[1] - cursor[0] + 1);
    (*ptr_last)->token = my_strncat_realloc((*ptr_last)->token,
                                            (argv + cursor[0]), size);
    (*ptr_last)->id = DELIMIT[index].id;
    (*ptr_last)->type = DELIMIT[index].type;
    cursor[1]++;
    cursor[0] = cursor[1];
    data = create_node("\0", 0, 0);
    add_node_at_the_end((*ptr_last), data);
}

static int goto_end_delim(char *argv, size_t *cursor, ssize_t index)
{
    size_t lenght = strlen(DELIMIT[index].end);
    size_t nb_open = 0;
    char *ptr_argv = argv + cursor[1];

    while (strncmp(ptr_argv, DELIMIT[index].end, lenght) || nb_open > 0) {
        if (!strncmp(ptr_argv, DELIMIT[index].end, lenght) && nb_open) {
            nb_open--;
        } else if (strncmp(ptr_argv, DELIMIT[index].start, lenght) == 0
                && DELIMIT[index].id == ID_PARENTHESE) {
            nb_open++;
        }
        cursor[1]++;
        ptr_argv = argv + cursor[1];
        if (argv[cursor[1]] == '\0')
            return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

int create_token(token_t *last, char *argv, size_t cursor[2], ssize_t index)
{
    token_t *data = NULL;

    first_block(&data, &last, argv, cursor);
    if (DELIMIT[index].type == D_NORMAL) {
        cursor[0] += strlen(DELIMIT[index].start);
        cursor[1] += strlen(DELIMIT[index].start);
    } else if (DELIMIT[index].type == D_DELIM) {
        cursor[1] += strlen(DELIMIT[index].start);
        if (goto_end_delim(argv, cursor, index) == EXIT_ERROR)
            return EXIT_ERROR;
        middle_block(&last, argv, cursor, index);
    } else {
        last_block(&data, &last, cursor, index);
    }
    return EXIT_SUCCESS;
}
