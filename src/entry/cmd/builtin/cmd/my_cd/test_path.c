/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** shell command function
*/

#include "shell.h"
#include "my_cd.h"

static void show_error_message(char *path)
{
    my_putstr_error(path);
    switch (errno) {
        case ENOENT:
            my_putstr_error(": No such file or directory.\n");
            break;
        case EACCES:
            my_putstr_error(": Permission denied.\n");
            break;
        case ENOTDIR:
            my_putstr_error(": Not a directory.\n");
            break;
        default:
            my_putstr_error(": ");
            my_putstr_error(strerror(errno));
            my_putstr_error(".\n");
    }
}

int test_opendir(char *path)
{
    DIR *dir = opendir(path);

    if (!dir) {
        show_error_message(path);
        return EXIT_ERROR;
    } else if (closedir(dir) == -1) {
        my_putstr_error("closedir : fail (test_opendir).\n");
    }
    return EXIT_SUCCESS;
}
