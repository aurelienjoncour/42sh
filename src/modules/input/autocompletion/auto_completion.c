/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** tab auto completion
*/

#include <stdlib.h>
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
    my_putstr(files->name);
    if (files->next != NULL)
        my_putchar('\t');
    else
        my_putchar('\n');
    print_list(files->next);
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
    }
    if (size >= 1)
        exit_value = complete_line(line, files, pos);
    free_list(files);
    return exit_value;
}