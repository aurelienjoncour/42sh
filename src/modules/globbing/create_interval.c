/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** create_interval
*/

#include "shell.h"

interval_t *create_interval(char c1, char c2)
{
    interval_t *interval = malloc(sizeof(interval_t));

    if (interval == NULL)
        return NULL;
    interval->c[0] = c1;
    interval->c[1] = c2;
    interval->next = NULL;
    return interval;
}