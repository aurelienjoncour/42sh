/*
** EPITECH PROJECT, 2020
** parser
** File description:
** add_node_at_the_end
*/

#include <stdlib.h>
#include "parser_t.h"
#include "parser.h"

token_t *get_last_token(token_t *token)
{
    token_t *last_token = token;

    if (token == NULL) {
        return NULL;
    }
    if (token->next != NULL)
        last_token = get_last_token(token->next);
    return last_token;
}

int add_node_at_the_end(token_t *node_1, token_t *node_2)
{
    token_t *last_node = get_last_token(node_1);

    if (last_node == NULL) {
        return EXIT_ERROR;
    }
    add_node(last_node, node_2);
    return EXIT_SUCCESS;
}

int list_push_node(token_t **list_dest, token_t *src)
{
    token_t *last_node = get_last_token(*list_dest);

    if (last_node == NULL) {
        *list_dest = src;
        return EXIT_SUCCESS;
    }
    add_node(last_node, src);
    return EXIT_SUCCESS;
}
