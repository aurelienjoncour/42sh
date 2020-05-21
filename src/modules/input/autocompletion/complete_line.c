/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** complete line
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "autocompletion.h"

static char *get_file_name(file_t *files, char *file_name)
{
    if (files == NULL)
        return file_name;
    for (int i = 0; files->name[i] != '\0' && file_name[i] != '\0'; i++)
        if (files->name[i] != file_name[i]) {
            file_name[i] = '\0';
            return get_file_name(files->next, file_name);
        }
    return file_name;
}

static void line_edit(char **line, size_t *pos, char **rest)
{
    int i = *pos;

    if (*pos < strlen(*line))
        *rest = *line + *pos;
    for (; i >= 0 && (*line)[i] != ' ' && (*line)[i] != '/'; i--);
    (*line)[i + 1] = '\0';
}

int complete_line(char **line, file_t *files, size_t *pos, bool multi)
{
    char *file_name = get_file_name(files->next, files->name);
    char *result;
    char *temp;
    char *rest = "";

    if (!*line)
        return EXIT_SUCCESS;
    line_edit(line, pos, &rest);
    temp = *line;
    *pos = my_strlen(*line) + my_strlen(file_name)
        + !(multi || file_name[my_strlen(file_name) - 1] == '/');
    result = my_strdupcat(4, *line, file_name,
        multi || file_name[my_strlen(file_name) - 1] == '/' ? "" : " ", rest);
    free(temp);
    if (result == NULL)
        return EXIT_ERROR;
    *line = result;
    return EXIT_SUCCESS;
}