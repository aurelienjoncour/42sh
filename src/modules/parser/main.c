/*
** EPITECH PROJECT, 2020
** parser
** File description:
** main
*/

#include <stdlib.h>
#include "node.h"
#include "parser.h"

static char *arg = " echo coucou \"comment lol mdr\" ca va | cat -e | grep coucou || ls | cat -e | grep include && pwd | grep home | cat -e";

int main(int ac, char **av)
{
    token_t *token = NULL;

    if (ac == 2) {
        token = tokeniser(arg);
        if (token == NULL)
            return EXIT_ERROR;
        display_list(token);
        destroy_list(token);
    } else {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}