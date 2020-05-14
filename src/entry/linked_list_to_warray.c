/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-14T14:03:46+02:00 | Author: simon
*/

#include "shell.h"

char **linked_list_to_warray(cmd_t *cmd)
{
    char **ret;
    size_t i = 0;

    if (!cmd || cmd->size == 0 || cmd->begin == NULL)
        return NULL;
    ret = malloc(sizeof(char *) * (cmd->size + 1));
    if (!ret)
        return NULL;
    ret[cmd->size] = NULL;
    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        ret[i] = my_strdup(ptr->token);
        if (!ret[i])
            return NULL;
        i++;
        if (i >= cmd->size) {
            break;
        }
    }
    return ret;
}
