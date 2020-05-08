/*
** EPITECH PROJECT, 2020
** parser
** File description:
** connect_node
*/

#include "parser.h"

void connect_node(token_t *node_1, token_t *node_2)
{
    node_1->next = node_2;
    node_2->prev = node_1;
}