/*
** EPITECH PROJECT, 2019
** Lib My - 04/03/2002
** File description:
** Word array utility tools
*/

#include "my.h"

int word_array_len(char **array)
{
    int len = 0;

    if (!array) {
        return 0;
    }
    for (size_t i = 0; array[i] != NULL; i++)
        len++;
    return len;
}

void word_array_destroy(char **array)
{
    if (!array) {
        return;
    }
    for (size_t i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

bool have_str_in_array(char **array, const int size, const char *str)
{
    if (!array) {
        return false;
    }
    for (size_t i = 0; i < (size_t)size; i++) {
        if (my_strcmp(array[i], str) == 0) {
            return true;
        }
    }
    return false;
}
