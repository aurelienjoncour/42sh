/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Search the binary file in PATH
*/

#include "shell.h"

static int manage_access_status(char **bin_path, char **eacces_bin_path)
{
    int ret = check_access_right_file(*bin_path);

    if (ret == EXIT_SUCCESS) {
        return 1;
    } else if (ret == EXIT_FAIL) {
        free(*eacces_bin_path);
        *eacces_bin_path = *bin_path;
        *bin_path = NULL;
    } else {
        free(*bin_path);
        *bin_path = NULL;
    }
    return 0;
}

static char *get_path_bin(const char *bin_name, char *path_list)
{
    char **path_array = my_str_to_word_array(path_list, ":");
    char *bin_path = NULL;
    char *eacces_bin_path = NULL;

    if (!path_array) {
        return NULL;
    }
    for (int i = 0; path_array[i] != NULL; i++) {
        bin_path = merge_path_filename(path_array[i], bin_name);
        if (manage_access_status(&bin_path, &eacces_bin_path)) {
            break;
        }
    }
    word_array_destroy(path_array);
    if (!bin_path && eacces_bin_path) {
        return eacces_bin_path;
    }
    return bin_path;
}

char *get_bin_path_search_bin(const char *cmd_name, shell_t *shell)
{
    char *path_list = NULL;
    char *bin_path = NULL;

    path_list = my_env_get_value(&shell->env, "PATH");
    if (!path_list) {
        return NULL;
    }
    bin_path = get_path_bin(cmd_name, path_list);
    free(path_list);
    return bin_path;
}
