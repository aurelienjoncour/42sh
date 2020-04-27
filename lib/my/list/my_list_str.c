/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** Created: 2020-04-01T09:26:57+02:00 | Author: simon
*/

#include "my.h"

static list_str_t *list_str_create_node(const char *str)
{
    list_str_t *node = NULL;

    node = malloc(sizeof(list_str_t));
    if (!node)
        return NULL;
    node->next = NULL;
    node->str = my_strdup(str);
    return node;
}

int my_str_list_add(list_str_t **list, const char *str)
{
    list_str_t *ptr = *list;

    if (!(*list)) {
        (*list) = list_str_create_node(str);
        if (!(*list))
            return EXIT_ERROR;
    } else {
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = list_str_create_node(str);
        if (!ptr->next) {
            return puterr("file_list_add : Error\n", EXIT_ERROR);
        }
    }
    return EXIT_SUCCESS;
}

char *my_str_list_read(list_str_t *list)
{
    static list_str_t *ptr = NULL;

    if (ptr == NULL) {
        if (list == NULL)
            return NULL;
        ptr = list;
    } else {
        ptr = ptr->next;
        if (ptr == NULL)
            return NULL;
    }
    return ptr->str;
}

void my_str_list_destroy(list_str_t *list)
{
    list_str_t *next_ptr = NULL;
    list_str_t *ptr = list;

    if (!list) {
        return;
    } else {
        do {
            next_ptr = ptr->next;
            free(ptr->str);
            free(ptr);
            ptr = next_ptr;
        } while (next_ptr);
    }
}
