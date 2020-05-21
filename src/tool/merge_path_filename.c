/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** tool function
*/

#include "shell.h"

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

int split_filepath(const char *str, char **ptr_path, char **ptr_filename)
{
    int idx_slash = -1;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '/') {
            idx_slash = (int)i;
        }
    }
    if (idx_slash == -1) {
        *ptr_path = my_strdup("./");
    } else {
        *ptr_path = my_strndup(str, (idx_slash + 1));
    }
    *ptr_filename = my_strdup(&str[idx_slash + 1]);
    if (!(*ptr_path) || !(*ptr_filename)) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
