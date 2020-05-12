/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-12T15:25:02+02:00 | Author: simon
*/

#include "shell.h"

extern const char *ERR_NO_SENSE;

static bool get_path_bin(const char *bin_name, char **path_array)
{
    char *bin_path = NULL;
    int ret;
    bool not_found = true;

    for (int i = 0; path_array[i] != NULL; i++) {
        bin_path = merge_path_filename(path_array[i], bin_name);
        ret = check_access_right_file(bin_path);
        if (ret == EXIT_SUCCESS || ret == EXIT_FAIL) {
            printf("%s\n", bin_path);
            not_found = false;
        }
        free(bin_path);
    }
    return not_found;
}

static int show_all_path(const char *cmd_name, shell_t *shell)
{
    char *path_list = NULL;
    char **path_array;
    int ret = EXIT_SUCCESS;

    path_list = my_env_get_value(&shell->env, "PATH");
    path_array = my_str_to_word_array(path_list, ":");
    if (!path_list || !path_array) {
        free(path_list);
        return EXIT_ERROR;
    }
    if (get_path_bin(cmd_name, path_array) == true) {
        ret = EXIT_FAIL;
    }
    free(path_list);
    word_array_destroy(path_array);
    return ret;
}

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

int where_show_all_path(const char *cmd_name, shell_t *shell)
{
    int ret;

    if (is_bin_path(cmd_name)) {
        printf("%s\n", ERR_NO_SENSE);
        return EXIT_ERROR;
    } else {
        ret = show_all_path(cmd_name, shell);
        if (ret != EXIT_SUCCESS) {
            return EXIT_ERROR;
        }
        return EXIT_SUCCESS;
    }
}
