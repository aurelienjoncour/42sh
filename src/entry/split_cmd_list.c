/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-13T08:40:44+02:00 | Author: simon
*/

#include "shell.h"

static size_t count_token(cmd_t *cmd, ID token_id, ID token2_id)
{
    size_t count = 1;

    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (ptr->id == token_id) {
            count++;
        } else if (token2_id != 0 && ptr->id == token2_id) {
            count++;
        }
    }
    return count;
}

static cmd_t **feed_array(cmd_t **dest, cmd_t *src, ID token_id, ID token2_id)
{
    size_t idx = 0;
    size_t size = 0;
    token_t *node;

    for (token_t *ptr = src->begin; ptr != NULL; ptr = ptr->next) {
        if (ptr->id == token_id || (token2_id && ptr->id == token2_id)) {
            dest[idx]->size = size;
            idx++;
            size = 0;
            continue;
        }
        node = create_node(ptr->token, ptr->id, ptr->type);
        list_push_node(&(dest[idx]->begin), node);
        size++;
    }
    dest[idx]->size = size;
    return dest;
}

cmd_t **split_cmd_list(cmd_t *cmd, ID token_id, ID token2_id)
{
    size_t size = count_token(cmd, token_id, token2_id);
    cmd_t **ret = NULL;

    if (size == 0)
        return NULL;
    ret = malloc(sizeof(cmd_t *) * (size + 1));
    if (!ret)
        return NULL;
    ret[size] = NULL;
    for (size_t i = 0; i < size; i++) {
        ret[i] = malloc(sizeof(cmd_t));
        if (!ret[i])
            return NULL;
        ret[i]->begin = NULL;
        ret[i]->end = NULL;
        ret[i]->size = 0;
    }
    ret = feed_array(ret, cmd, token_id, token2_id);
    return ret;
}
