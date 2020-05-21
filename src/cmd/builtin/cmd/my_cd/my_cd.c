/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** shell command function
*/

#include "shell.h"
#include "my_cd.h"

static void update_variable(shell_t *shell)
{
    char *env_cmd[4] = {"setenv", "PWD", NULL, NULL};
    char *local_env_cmd[3] = {"set", NULL, NULL};

    env_cmd[2] = getcwd(NULL, 0);
    local_env_cmd[1] = malloc(sizeof(char) * (my_strlen(env_cmd[2]) + 5));
    if (local_env_cmd[1] != NULL) {
        local_env_cmd[1][0] = '\0';
        local_env_cmd[1] = my_strcat(local_env_cmd[1], "cwd=");
        local_env_cmd[1] = my_strcat(local_env_cmd[1], env_cmd[2]);
        my_set(local_env_cmd, shell);
        free(local_env_cmd[1]);
    }
    my_setenv(env_cmd, shell);
    free(env_cmd[2]);
}

int my_cd(char **cmd, shell_t *shell)
{
    char *path;

    path = my_cd_get_path(cmd, shell);
    if (path && test_opendir(path) == EXIT_SUCCESS) {
        free(shell->prev_path);
        shell->prev_path = getcwd(NULL, 0);
        if (chdir(path) == -1) {
            my_putstr_error("my_cd: error - change directory\n");
        }
        update_variable(shell);
        shell->exit_status = SUCCESS_STATUS;
    } else {
        shell->exit_status = ERROR_STATUS;
    }
    free(path);
    return EXIT_SUCCESS;
}
