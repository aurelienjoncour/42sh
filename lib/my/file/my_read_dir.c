/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** Created: 2020-03-25T14:34:11+01:00 | Author: simon
*/

#include <sys/types.h>
#include <dirent.h>

#include "my.h"

int my_read_dir(file_list_t **files, const char *dirpath)
{
    struct dirent *file;
    DIR *dir = opendir(dirpath);
    int size = 0;

    if (!dir) {
        my_putstr_error("read_filedir: Fail to open directory\n");
        return (-1);
    }
    (*files) = NULL;
    while ((file = readdir(dir)) != NULL) {
        if (file->d_type == DT_REG) {
            size++;
            my_file_list_add(files, file->d_name);
        }
    }
    closedir(dir);
    return size;
}

static file_list_t *file_list_create_node(const char *filename)
{
    file_list_t *node = NULL;

    node = malloc(sizeof(file_list_t));
    if (!node)
        return NULL;
    node->next = NULL;
    node->name = my_strdup(filename);
    return node;
}

int my_file_list_add(file_list_t **list, const char *filename)
{
    file_list_t *ptr = *list;

    if (!(*list)) {
        (*list) = file_list_create_node(filename);
        if (!(*list))
            return EXIT_FAILURE;
    } else {
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = file_list_create_node(filename);
        if (!ptr->next) {
            my_putstr_error("file_list_add : Error\n");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

char *my_file_list_read(file_list_t *list)
{
    static file_list_t *ptr = NULL;

    if (ptr == NULL) {
        if (list == NULL)
            return NULL;
        ptr = list;
    } else {
        ptr = ptr->next;
        if (ptr == NULL)
            return NULL;
    }
    return ptr->name;
}

void my_file_list_destroy(file_list_t *list)
{
    file_list_t *next_ptr = NULL;
    file_list_t *ptr = list;

    if (!list) {
        return;
    } else {
        do {
            next_ptr = ptr->next;
            free(ptr->name);
            free(ptr);
            ptr = next_ptr;
        } while (next_ptr);
    }
}
