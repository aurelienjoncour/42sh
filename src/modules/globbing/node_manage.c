/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-15T08:53:41+02:00 | Author: simon
*/

#include "globbing.h"

void remove_invalid_node(file_list_t *del_node, file_list_t *prev_node,
file_list_t **first_node)
{
    if (!del_node || !first_node) {
        return;
    }
    if (prev_node == NULL) {
        *first_node = del_node->next;
    } else {
        prev_node->next = del_node->next;
    }
    free(del_node->name);
    free(del_node);
}

token_t *file_list_to_token_list(file_list_t *file_list, char *path)
{
    token_t *list = NULL;
    token_t *new;
    char *value;

    for (file_list_t *ptr = file_list; ptr != NULL; ptr = ptr->next) {
        value = my_str_concat(path, ptr->name);
        if (!value) {
            return NULL;
        }
        new = create_node(value, ID_WITHOUT, 0);
        list_push_node(&list, new);
        free(value);
    }
    return list;
}

void insert_new_token(token_t *old, token_t *new_first, token_t *new_last,
cmd_t *main_cmd)
{
    token_t *prev = old->prev;
    token_t *post = old->next;

    if (prev != NULL) {
        prev->next = new_first;
    } else {
        main_cmd->begin = new_first;
    }
    if (post != NULL) {
        post->prev = new_last;
    } else {
        main_cmd->end = new_last;
    }
}
