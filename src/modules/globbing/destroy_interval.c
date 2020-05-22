/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** destroy_interval
*/

#include "shell.h"

void destroy_interval(interval_t *data)
{
    if (data->next != NULL)
        destroy_interval(data->next);
    free(data);
}