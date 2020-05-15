/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-13T11:23:23+02:00 | Author: simon
*/

#include "parser.h"

static token_t *get_last_token_and_size(token_t *start, size_t *size)
{
    token_t *ptr = start;

    (*size) = 0;
    while (true) {
        if (ptr->next == NULL) {
            break;
        }
        ptr = ptr->next;
        (*size)++;
    }
    if (*size != 0) {
        (*size)++;
    }
    return ptr;
}

static void token_list_clean(token_t *start)
{
    token_t *next;

    for (token_t *i = start; i != NULL;) {
        if (i->token[0] == '\0' || i->id == ID_SPACE || i->id == ID_TAB) {
            next = i->next;
            rm_node(i);
            i = next;
        }
        if (i != NULL)
            i = i->next;
    }
}

cmd_t *parse_entry(char *entry)
{
    cmd_t *cmd = malloc(sizeof(cmd_t));

    if (!cmd) {
        return NULL;
    }
    cmd->begin = tokeniser(entry);
    token_list_clean(cmd->begin);
    if (!cmd->begin) {
        free(cmd);
        return NULL;
    }
    cmd->end = get_last_token_and_size(cmd->begin, &(cmd->size));
    return cmd;
}

void cmd_destroy(cmd_t *cmd)
{
    destroy_list(cmd->begin);
    free(cmd);
}

void cmd_array_destroy(cmd_t **cmd_array)
{
    for (size_t i = 0; cmd_array[i] != NULL; i++) {
        if (cmd_array[i]->begin != NULL)
            destroy_list(cmd_array[i]->begin);
        free(cmd_array[i]);
    }
    free(cmd_array);
}
