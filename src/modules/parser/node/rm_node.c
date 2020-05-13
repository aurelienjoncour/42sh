/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** rm_node
*/

#include <stdlib.h>
#include "parser_t.h"

static void rm_last_node(token_t *deleted)
{
    if (deleted->prev != NULL)
        deleted->prev->next = NULL;
    free(deleted->token);
    free(deleted);
}

token_t *rm_node(token_t *deleted)
{
    token_t *new_node = deleted->next;

    if (new_node == NULL) {
        rm_last_node(deleted);
        return NULL;
    }
    new_node->prev = deleted->prev;
    if (deleted->prev != NULL)
        deleted->prev->next = new_node;
    free(deleted->token);
    free(deleted);
    return new_node;
}
