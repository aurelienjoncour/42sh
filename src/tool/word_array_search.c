/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** tool function
*/

#include "minishell.h"

int word_array_search(char **array, const int size, const char *str)
{
    for (ssize_t i = 0; i < size; i++) {
        if (my_strcmp(array[i], str) == 0) {
            return i;
        }
    }
    return -1;
}

int word_array_search2(const char **array, const int size, const char *str)
{
    for (ssize_t i = 0; i < size; i++) {
        if (my_strcmp(array[i], str) == 0) {
            return i;
        }
    }
    return -1;
}
