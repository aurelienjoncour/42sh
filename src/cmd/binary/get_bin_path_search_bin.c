/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** Search the binary file in PATH
*/

#include "minishell.h"

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

static char *get_path_bin(char *bin_name, char *path_list)
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

int get_bin_path_search_bin(char ***cmd, minishell_t *shell)
{
    char *name_cmd = (*cmd)[0];
    char *path_list = NULL;
    char *bin_path = NULL;

    path_list = my_env_get_value(&shell->env, "PATH");
    if (!path_list) {
        free(path_list);
        return EXIT_FAIL;
    }
    bin_path = get_path_bin(name_cmd, path_list);
    if (bin_path) {
        (*cmd)[0][0] = '\0';
        (*cmd)[0] = bin_path;
        free(path_list);
        return EXIT_SUCCESS;
    }
    free(path_list);
    return EXIT_FAIL;
}
