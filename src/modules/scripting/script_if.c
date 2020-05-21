/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-19T15:35:23+02:00 | Author: simon
*/

#include "shell.h"

static const char *IF_TOKEN = "if";

static bool is_if_condition(cmd_t *cmd)
{
    if (cmd->begin && cmd->begin->id == ID_WITHOUT
        && strcmp(cmd->begin->token, IF_TOKEN) == 0) {
        return true;
    }
    return false;
}

int eval_if_condition(cmd_t *cmd)
{
    if (is_if_condition(cmd) == false) {
        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}
