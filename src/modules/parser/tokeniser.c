/*
** EPITECH PROJECT, 2020
** parser
** File description:
** tokeniser
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "node.h"

static char *my_strncat_realloc(char *s1, char *s2, size_t n)
{
    char *result = malloc(sizeof(char) * (strlen(s1) + n +1));

    if (result == NULL)
        return NULL;
    strcpy(result, s1);
    strncat(result, s2, n);
    free(s1);
    return result;
}

static ssize_t is_special_id(char *str, size_t cursor[2])
{
    for (ssize_t i = 0; delimit[i].start != 0; i++) {
        if (!strncmp(delimit[i].start, str+cursor[1], strlen(delimit[i].start))) {
            return i;
        }
    }
    return -1;
}

int create_token(token_t *last, char *argv, size_t cursor[2], ssize_t index)
{
    token_t *data = NULL;

    if (cursor[0] != cursor[1]) {
        if (strlen(last->token)) {
            data = create_node("\0", 0, 0);
            add_node_at_the_end(last, data);
        }
        last = get_last_token(last);
        last->token = my_strncat_realloc(last->token, argv+cursor[0], cursor[1] - cursor[0]);
        cursor[0] = cursor[1];
        data = create_node("\0", 0, 0);
        add_node_at_the_end(last, data);
    }
    if (delimit[index].type == D_NORMAL) {
        cursor[0] += strlen(delimit[index].start);
        cursor[1] += strlen(delimit[index].start);
    } else if (delimit[index].type == D_DELIM) {
        printf("La\n");
        cursor[1] += strlen(delimit[index].start);
        while (strncmp(argv+cursor[1], delimit[index].end, strlen(delimit[index].end))) {
            cursor[1]++;
            if (argv[cursor[1]] == '\0')
                return EXIT_ERROR;
        }
        if (strlen(last->token)) {
            data = create_node("\0", 0, 0);
            add_node_at_the_end(last, data);
        }
        last = get_last_token(last);
        last->token = my_strncat_realloc(last->token, argv+cursor[0], cursor[1] - cursor[0] + 1);
        last->id = delimit[index].id;
        last->type = delimit[index].type;
        cursor[1]++;
        printf("->%s\n", argv+cursor[1]);
        cursor[0] = cursor[1];
        data = create_node("\0", 0, 0);
        add_node_at_the_end(last, data);

    } else {
        if (strlen(last->token)) {
            data = create_node("\0", 0, 0);
            add_node_at_the_end(last, data);
        }
        last = get_last_token(last);
        last->token = my_strncat_realloc(last->token, delimit[index].start, strlen(delimit[index].start));
        last->id = delimit[index].id;
        last->type = delimit[index].type;
        cursor[1] += strlen(delimit[index].start);
        cursor[0] = cursor[1];
        data = create_node("\0", 0, 0);
        add_node_at_the_end(last, data);
    }
    return EXIT_SUCCESS;
}


token_t *tokeniser(char *argv)
{
    ssize_t index = 0;
    size_t cursor[2] = {0};
    token_t *start = create_node("\0", ID_WIHOUT, D_NORMAL);
    token_t *last = NULL;
    token_t *data = NULL;

    if (start == NULL)
        return NULL;
    while (argv[cursor[1]] != '\0') {
        printf("%s\n", argv+cursor[1]);
        index = is_special_id(argv, cursor);
        if (index == -1) {
            cursor[1]++;
        } else {
            last = get_last_token(start);
            if (create_token(last, argv, cursor, index) == EXIT_ERROR)
                return NULL;
        }
    }
    last = get_last_token(last);
    if (strlen(last->token)) {
        data = create_node("\0", 0, 0);
        add_node_at_the_end(last, data);
        last = get_last_token(last);
    }
    last->token = my_strncat_realloc(last->token, argv+cursor[0], cursor[1] - cursor[0] + 1);
    return start;
}