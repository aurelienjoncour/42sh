/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** add_interval
*/

#include "shell.h"
#include "globbing.h"

int add_interval(interval_t *data, char c1, char c2)
{
    interval_t *tmp = data;

    if (data == NULL)
        return EXIT_ERROR;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = create_interval(c1, c2);
    if (tmp->next == NULL)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}