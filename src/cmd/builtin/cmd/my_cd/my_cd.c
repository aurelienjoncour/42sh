/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** shell command function
*/

#include "shell.h"
#include "my_cd.h"

int my_cd(char **cmd, shell_t *shell)
{
    char *path;
    char *env_cmd[4] = {"setenv", "PWD", NULL, NULL};

    path = my_cd_get_path(cmd, shell);
    if (path && test_opendir(path) == EXIT_SUCCESS) {
        free(shell->prev_path);
        shell->prev_path = getcwd(NULL, 0);
        if (chdir(path) == -1) {
            my_putstr_error("my_cd: error - change directory\n");
        }
        env_cmd[2] = getcwd(NULL, 0);
        my_setenv(env_cmd, shell);
        free(env_cmd[2]);
        shell->exit_status = SUCCESS_STATUS;
    } else {
        shell->exit_status = ERROR_STATUS;
    }
    free(path);
    return EXIT_SUCCESS;
}
