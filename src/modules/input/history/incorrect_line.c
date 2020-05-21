/*
** EPITECH PROJECT, 2019
** 52sh
** File description:
** 53sh
*/

#include "shell.h"

bool incorrect_line(char *new_line)
{
    for (size_t i = 0; new_line[i]; i++)
        if (new_line[i] != ' ')
            return false;
    return true;
}