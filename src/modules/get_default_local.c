/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Get default local env
*/

#include "shell.h"

static int add_local_var_from_env(char **local, char *local_name, char **env,
char *env_name)
{
    bool found = false;

    for (size_t i = 0; env[i]; i++) {
        if (my_strncmp(env[i], env_name, my_strlen(env_name)) == 0) {
            *local = malloc(sizeof(char) * (my_strlen(env[i]) -
            my_strlen(env_name) + my_strlen(local_name) + 1));
            found = true;
        }
        if (found == true && *local != NULL) {
            *local[0] = '\0';
            *local = my_strcat(*local, local_name);
            *local = my_strcat(*local, &env[i][my_strlen(env_name)]);
            return EXIT_SUCCESS;
        } else if (found == true && *local == NULL)
            return EXIT_ERROR;
    }
    *local = NULL;
    return EXIT_SUCCESS;
}

static int add_cwd(char **local)
{
    char *location = getcwd(NULL, 0);

    *local = malloc(sizeof(char) * (my_strlen(location) + 5));
    if (local == NULL)
        return 0;
    *local[0] = '\0';
    *local = my_strcat(*local, "cwd=");
    *local = my_strcat(*local, location);
    free(location);
    return 1;
}

char **get_default_local(char **env)
{
    char **local = malloc(sizeof(char *) * 3);
    int return_value = 0;
    char *local_names[] = {"term=", NULL};
    char *env_names[] = {"TERM=", NULL};
    int pos[] = {0, 0};

    if (local == NULL)
        return NULL;
    pos[0] += add_cwd(&local[0]);
    while (env != NULL && local_names[pos[1]] != NULL) {
        return_value = add_local_var_from_env(&local[pos[0]],
        local_names[pos[1]], env, env_names[pos[1]]);
        if (return_value == EXIT_ERROR)
            return NULL;
        if (local[pos[0]] != NULL)
            pos[0]++;
        pos[1]++;
    }
    local[pos[0]] = NULL;
    return local;
}
