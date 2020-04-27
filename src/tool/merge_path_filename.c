/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** tool function
*/

#include "minishell.h"

char *merge_path_filename(const char *path, const char *filename)
{
    int sizea = my_strlen(path);
    int sizeb = my_strlen(filename);
    char *merge = malloc(sizeof(char) * (sizea + sizeb + 2));

    if (!merge) {
        my_putstr_error("ERORR: malloc : merge_str() \n");
        return NULL;
    }
    if (path[0] != '\0')
        my_strcpy(merge, path);
    if (path[sizea - 1] != '/' && path[0] != '\0') {
        merge[sizea] = '/';
        sizea++;
    }
    if (filename[0] != '\0')
        my_strcpy(&merge[sizea], filename);
    merge[sizea + sizeb] = '\0';
    return merge;
}
