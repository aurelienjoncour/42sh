/*
** EPITECH PROJECT, 2020
** parser
** File description:
** destroy_list
*/

#include <stdlib.h>
#include "parser_t.h"

void destroy_list(token_t *ptr)
{
    free(ptr->token);
    if (ptr->prev != NULL)
        free(ptr->prev);
    if (ptr->next != NULL) {
        destroy_list(ptr->next);
    } else {
        free(ptr);
    }
}