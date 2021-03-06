/*
** EPITECH PROJECT, 2019
** CPool_Day10_2019
** File description:
** Task04
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

static char **swap_if_true(char **array, int i,
char *sorted, int (*cmp)(char const *, char const *))
{
    char *temp;

    if (cmp(array[i], array[i + 1]) > 0) {
        temp = &array[i][0];
        array[i] = &array[i + 1][0];
        array[i + 1] = temp;
        *sorted = 'F';
    }
    return array;
}

char **my_advanced_sort_word_array(
char **tab, int (*cmp)(char const *, char const *), ssize_t size)
{
    char is_sorted = 'T';

    do {
        is_sorted = 'T';
        for (ssize_t i = 0; i < (size - 1); i++)
            tab = swap_if_true(tab, i, &is_sorted, cmp);
    } while (is_sorted == 'F');
    return tab;
}
