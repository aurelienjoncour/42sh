/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-14T14:03:46+02:00 | Author: simon
*/

#include "shell.h"

static bool is_valid_token(token_t *token)
{
    if (token->id == ID_BACKGROUND || token_is_file_redirect(token->id)) {
        return false;
    } else if (token->prev && token_is_file_redirect(token->prev->id)) {
        return false;
    }
    return true;
}

static size_t get_size_warray(cmd_t *cmd)
{
    size_t count = 0;

    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (is_valid_token(ptr)) {
            count++;
        }
    }
    return count;
}

static char **feed_warray(cmd_t *cmd, char **ret, size_t size)
{
    size_t i = 0;

    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (is_valid_token(ptr) == false)
            continue;
        ret[i] = my_strdup(ptr->token);
        if (!ret[i])
            return NULL;
        i++;
        if (i >= size)
            break;
    }
    return ret;
}

char **linked_list_to_warray(cmd_t *cmd)
{
    char **ret;
    size_t size = get_size_warray(cmd);

    if (!cmd || size == 0 || cmd->begin == NULL)
        return NULL;
    ret = malloc(sizeof(char *) * (size + 1));
    if (!ret)
        return NULL;
    ret[size] = NULL;
    return feed_warray(cmd, ret, size);
}
