/*
** EPITECH PROJECT, 2020
** parser
** File description:
** main
*/

#include "parser.h"
#include "parser_t.h"

//static char *arg = " echo coucou \"comment lol mdr\" ca va | cat -e | grep coucou || ls | cat -e | grep include && pwd | grep home | cat -e";
static char *arg = " \\(echo coucou \"comment lol mdr\" ca va) | cat -e | grep coucou \\|| ls | cat -e | grep include && pwd | grep home | cat -e";
//static char *arg = "echo \\\"\\\"";

int main(int ac, char **av)
{
    cmd_t *cmd;

    if (ac == 2) {
        cmd = parse_entry(arg);
        if (cmd == NULL)
            return EXIT_ERROR;
        display_list(cmd->begin);
        cmd_destroy(cmd);
    } else {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
