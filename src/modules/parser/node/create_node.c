/*
** EPITECH PROJECT, 2020
** parser
** File description:
** create_node
*/

#include <stdlib.h>
#include <string.h>
#include "parser.h"

static void init_value_node(token_t *node, ID id, TYPE type)
{
    node->id = id;
    node->type = type;
    node->next = NULL;
    node->prev = NULL;
}

token_t *create_node(char *token, ID id, TYPE type)
{
    token_t *node = malloc(sizeof(token_t));

    if (node == NULL)
        return NULL;
    if (token == NULL) {
        node->token = malloc(sizeof(char));
        if (node->token == NULL)
            return NULL;
        node->token[0] = '\0';
    } else {
        node->token = strdup(token);
        if (node->token == NULL)
            return NULL;
    }
    if (node->token == NULL)
        return NULL;
    init_value_node(node, id, type);
    return node;
}