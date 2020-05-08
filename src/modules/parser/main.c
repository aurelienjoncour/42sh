/*
** EPITECH PROJECT, 2020
** parser
** File description:
** main
*/

#include <stdlib.h>
#include "node.h"
#include "parser.h"

int main(int ac, char **av)
{
    token_t *token = NULL;

    if (ac == 2) {
        token = tokeniser(av[1]);
        display_list(token);
        destroy_list(token);
    } else {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}