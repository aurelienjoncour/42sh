/*
** EPITECH PROJECT, 2019
** 48sh
** File description:
** 49sh
*/

#include "my.h"

static size_t get_list_size(file_list_t *list)
{
    size_t i;
    file_list_t *move = list;

    for (i = 0; move; move = move->next, i++);
    return i - 1;
}

static void tab_filler(file_list_t *list, file_list_t **tab)
{
    file_list_t *move = list;

    for (size_t i = 0; move->next; move = move->next, i++) {
        tab[i] = move;
        tab[i + 1] = NULL;
    }
}

static void move_it(file_list_t **list, file_list_t **tab)
{
    file_list_t *move = *list;

    for (ssize_t i = 0; tab[i + 1]; i++) {
        move = tab[i];
        tab[i]->next = tab[i + 1];
        tab[i + 1]->next = NULL;
        move = move->next;
    }
    *list = tab[0];
}

bool sort_file_list(file_list_t **list)
{
    size_t size = get_list_size(*list);
    file_list_t *tmp;
    file_list_t **tab;

    if (size == 1)
        return true;
    tab = malloc(sizeof(file_list_t *) * (size + 1));
    if (!tab)
        return false;
    tab_filler(*list, tab);
    for (ssize_t i = 0; tab[i + 1]; i++)
        if (my_strcmp(tab[i]->name, tab[i + 1]->name) > 0) {
            tmp = tab[i];
            tab[i] = tab[i + 1];
            tab[i + 1] = tmp;
            i = -1;
        }
    move_it(list, tab);
    free(tab);
    return true;
}