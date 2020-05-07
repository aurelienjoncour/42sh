/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** function
*/

#include "shell.h"

static int is_bin_path(char *str)
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

int get_bin_path(char ***ptr_cmd, shell_t *shell)
{
    char *name_cmd = (*ptr_cmd)[0];

    if (is_bin_path(name_cmd)) {
        if (check_access_right_file(name_cmd) == EXIT_ERROR) {
            return EXIT_FAIL;
        } else {
            return EXIT_SUCCESS;
        }
    } else {
        return get_bin_path_search_bin(ptr_cmd, shell);
    }
}
