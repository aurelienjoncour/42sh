/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-12T14:06:13+02:00 | Author: simon
*/

#include "shell.h"

extern const char *BUILTIN_NAME[];

static const char *ERR_FEW_ARG = "which: Too few arguments.";
static const char *ERR_NOT_FOUND = ": Command not found.";
static const char *INFO_BUILTIN = ": shell built-in command.";

static bool is_builtin_cmd(const char *cmd_name)
{
    for (size_t i = 0; BUILTIN_NAME[i] != NULL; i++) {
        if (strcmp(BUILTIN_NAME[i], cmd_name) == 0) {
            return true;
        }
    }
    return false;
}

static int check_for_binary_cmd(const char *cmd_name, shell_t *shell)
{
    char *path_cmd = NULL;

    if (get_bin_path(cmd_name, &path_cmd, shell) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    if (path_cmd == NULL) {
        return EXIT_ERROR;
    }
    printf("%s\n", path_cmd);
    free(path_cmd);
    return EXIT_SUCCESS;
}

static int process_command_name(const char *cmd_name, shell_t *shell,
bool *not_found)
{
    int ret;

    if (is_builtin_cmd(cmd_name) == true) {
        printf("%s%s\n", cmd_name, INFO_BUILTIN);
        return EXIT_SUCCESS;
    }
    ret = check_for_binary_cmd(cmd_name, shell);
    if (ret == EXIT_ERROR) {
        my_putstr_error(ERR_NOT_FOUND);
        *not_found = true;
    }
    return EXIT_SUCCESS;
}

int my_which(char **cmd, shell_t *shell)
{
    bool not_found = false;

    if (word_array_len(cmd) == 1) {
        shell->exit_status = ERROR_STATUS;
        my_putstr_error(ERR_FEW_ARG);
        return EXIT_SUCCESS;
    }
    for (size_t i = 1; cmd[i] != NULL; i++) {
        if (process_command_name(cmd[i], shell, &not_found) != EXIT_SUCCESS) {
            return EXIT_ERROR;
        }
    }
    if (not_found == true) {
        shell->exit_status = ERROR_STATUS;
    } else {
        shell->exit_status = SUCCESS_STATUS;
    }
    return EXIT_SUCCESS;
}
