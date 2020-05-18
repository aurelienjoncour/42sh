/*
** EPITECH PROJECT, 2020
** 42sh
** File description:
** read_file
*/

#include <stdlib.h>
#include "shell.h"
#include "my.h"

static bool rec_read(char ***ret, int size, int const fd)
{
    char *tmp = get_next_line(fd);

    if (tmp && size < MAX_LINE) {
        if (!rec_read(ret, size + 1, fd))
            return false;
    }
    else {
        free(tmp);
        *ret = malloc(sizeof(char *) * (size + 1));
        if (!(*ret))
            return false;
        (*ret)[size] = NULL;
        return true;
    }
    if (tmp[my_strlen(tmp) - 1] == '\n')
        tmp[my_strlen(tmp) - 1] = '\0';
    (*ret)[size] = tmp;
    return true;
}

char **read_file(int const fd)
{
    char **ret;

    rec_read(&ret, 0, fd);
    if (!ret)
        return NULL;
    return ret;
}

void destroy_file(char **file)
{
    for (size_t i = 0; file[i]; i++)
        free(file[i]);
    free(file);
}