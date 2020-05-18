/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-15T08:53:41+02:00 | Author: simon
*/

#include "globbing.h"

const char *ERR_NO_MATCH = "%s: No match.\n";

static char *get_filepath(const char *str)
{
    int idx_slash = -1;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '/') {
            idx_slash = (int)i;
        }
    }
    if (idx_slash == -1) {
        return my_strdup("./");
    } else {
        return my_strndup(str, (idx_slash + 1));
    }
}

char **globbing(const char *str, const char *cmd_name)
{
    char *path = get_filepath(str);
    file_list_t *filenames;
    int size;

    size = my_read_dir(&filenames, path);
    if (size == -1) {
        free(path);
        my_putstr_error("globbing: fail to browse directory.\n");
        return NULL;
    } else if (size == 0) {
        fprintf(stderr, ERR_NO_MATCH, cmd_name);
        return NULL;
    }
    return NULL;
}
