/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** tab auto completion
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "my_key.h"
#include "autocompletion.h"

static void free_list(file_t *files)
{
    if (files == NULL)
        return;
    free_list(files->next);
    free(files->name);
    free(files);
}

static int get_list_size(file_t *files, int i)
{
    if (files == NULL || i > 1)
        return i;
    return get_list_size(files->next, i + 1);
}

static void print_list(file_t *files)
{
    if (files == NULL)
        return;
    fprintf(stdout, "%s\t", files->name);
    print_list(files->next);
}

static int complete_line(char **line, char *file_name, size_t *pos)
{
    char *result;
    char *temp;
    char *rest = "";
    int i = *pos;

    if (*pos < strlen(*line))
        rest = *line + *pos;
    for (; (*line)[i] != ' ' && (*line)[i] != '/'; i--);
    (*line)[i + 1] = '\0';
    temp = *line;
    *pos = my_strlen(*line) + my_strlen(file_name);
    result = my_strdupcat(4, *line, file_name,
        file_name[my_strlen(file_name) - 1] == '/' ? "" : " ", rest);
    free(temp);
    if (result == NULL)
        return EXIT_ERROR;
    *line = result;
    return EXIT_SUCCESS;
}

int check_tab(char **line, size_t *pos, int ch, env_t *env)
{
    file_t *files;
    int size;
    int exit_value = EXIT_FAILURE;

    if (ch != STAB)
        return EXIT_FAILURE;
    files = get_files(*line, *pos, env);
    size = get_list_size(files, 0);
    if (size > 1) {
        my_putchar('\n');
        print_list(files);
        exit_value = EXIT_SUCCESS;
    } else if (size == 1)
        exit_value = complete_line(line, files->name, pos);
    free_list(files);
    return exit_value;
}