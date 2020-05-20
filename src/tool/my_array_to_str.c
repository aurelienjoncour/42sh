/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Turn an arry into a single string
*/

#include <unistd.h>
#include <stdbool.h>
#include "my.h"
#include "shell_t.h"

char *my_array_to_str(char **tab, bool parent)
{
    int size = 0;
    char *str;
    int i_tab = 0;

    for (; tab[i_tab] != NULL; i_tab++)
        size += my_strlen(tab[i_tab]) + 1;
    str = malloc(sizeof(char) * size + 1 + (i_tab > 1 ? 2 : 0));
    if (str == NULL)
        return NULL;
    if (i_tab > 1 && parent)
        str[1] = '\0';
    str[0] = i_tab > 1 && parent ? '(' : '\0';
    for (int i = 0; tab[i] != NULL; i++) {
        my_strcat(str, tab[i]);
        my_strcat(str, " ");
    }
    str[my_strlen(str) - 1] = '\0';
    if (i_tab > 1 && parent)
        my_strcat(str, ")");
    return str;
}