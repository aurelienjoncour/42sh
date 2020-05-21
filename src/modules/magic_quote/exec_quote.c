/*
** EPITECH PROJECT, 2019
** 44sh
** File description:
** 45sh
*/

#include "shell.h"

int load_magic_quote(shell_t *shell, cmd_t *cmd, int *exit_status)
{
    bool quote = false;
    token_t *move = cmd->begin;
    int ret;

    *exit_status = SUCCESS_STATUS;
    while (move) {
        if (move->id == ID_BACK_QUOTE) {
            ret = get_magic_quote(shell, &move->token);
            if (!move->token)
                return EXIT_ERROR;
            if (ret != 0) {
                *exit_status = ret;
            }
            quote = true;
        }
        move = move->next;
    }
    if (quote)
        return HAVE_MQUOTE;
    return NO_MQUOTE;
}
