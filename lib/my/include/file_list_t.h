/*
** EPITECH PROJECT, 2020
** LIBMY
** File description:
** Created: 2020-03-25T14:34:11+01:00 | Author: simon
*/

#ifndef H_FILE_LIST
#define H_FILE_LIST

typedef struct file_list {
    struct file_list *next;
    char *name;
} file_list_t;

#endif
