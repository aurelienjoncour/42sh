/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** function
*/

#include "shell.h"

int check_access_right_file(const char *bin_path)
{
    int ret;

    if (!bin_path) {
        return EXIT_ERROR;
    }
    ret = access(bin_path, F_OK | X_OK);
    if (ret == 0) {
        return EXIT_SUCCESS;
    } else {
        if (errno == EACCES) {
            return EXIT_FAIL;
        }
        return EXIT_ERROR;
    }
}
