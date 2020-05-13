/*
** EPITECH PROJECT, 2020
** parser
** File description:
** display_list
*/

#include <stdio.h>
#include <stdlib.h>
#include "parser_t.h"

void display_list(token_t *start)
{
    if (start == NULL)
        return;
    printf("|ID:%d|TYPE:%d|%s->\n", start->id, start->type, start->token);
    if (start->next != NULL)
        display_list(start->next);
}
