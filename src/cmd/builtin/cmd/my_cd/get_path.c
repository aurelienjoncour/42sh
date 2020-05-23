/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** shell command function
*/

#include "shell.h"
#include "my_cd.h"

static char *convert_path(char *path, char *last_path, env_t *env)
{
    char *home_path = my_env_get_value(env, "HOME");
    char *ret = NULL;
    bool have_home_char = !my_strncmp(path, "~/", 2) || !my_strcmp(path, "~");

    if (path && !my_strcmp(path, "-")) {
        if (!last_path) {
            my_putstr_error(": No such file or directory.");
        } else {
            ret = my_strdup(last_path);
        }
    } else if (have_home_char && home_path) {
        ret = malloc(sizeof(char) * (my_strlen(path) + my_strlen(home_path)));
        my_strcpy(ret, home_path);
        my_strcpy(ret + my_strlen(home_path), path + 1);
    } else {
        ret = my_strdup(path);
    }
    free(path);
    free(home_path);
    return ret;
}

char *my_cd_get_path(char **cmd, shell_t *shell)
{
    int len = word_array_len(cmd);
    char *path;
    char *corrected_path;

    if (len < 1) {
        my_putstr_error("cd: Empty command.\n");
        return NULL;
    } else if (len > 2) {
        my_putstr_error("cd: Too many arguments.\n");
        return NULL;
    }
    if (len == 2) {
        path = my_strdup(cmd[1]);
    } else if (len == 1) {
        path = my_strdup("~");
    }
    if (!path)
        return NULL;
    corrected_path = convert_path(path, shell->prev_path, &shell->env);
    return corrected_path;
}
