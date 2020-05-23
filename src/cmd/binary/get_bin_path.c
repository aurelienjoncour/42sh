/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** function
*/

#include "shell.h"

static int is_bin_path(const char *str)
{
    int len = my_strlen(str);

    if (len >= 1 && str[0] == '/') {
        return 1;
    }
    if (!my_strncmp(str, "./", 2)) {
        return 1;
    } else if (!my_strncmp(str, "../", 3)) {
        return 1;
    }
    if (str && have_slash(str)) {
        return 1;
    }
    return 0;
}

int get_bin_path(const char *cmd_name, char **ptr_path, shell_t *shell)
{
    char *bin_path = NULL;

    *ptr_path = NULL;
    if (is_bin_path(cmd_name)) {
        if (check_access_right_file(cmd_name) == EXIT_ERROR) {
            return EXIT_ERROR;
        } else {
            *ptr_path = my_strdup(cmd_name);
            if (!(*ptr_path))
                return EXIT_ERROR;
            return EXIT_SUCCESS;
        }
    } else {
        bin_path = get_bin_path_search_bin(cmd_name, shell);
        if (!bin_path) {
            return EXIT_ERROR;
        }
        *ptr_path = bin_path;
        return EXIT_SUCCESS;
    }
}
