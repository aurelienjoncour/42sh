/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** shell command function
*/

#include "my.h"

static int print_alias(char **cmd, shell_t *shell)
{
    char *str = my_env_get_value(shell->alias, argv[1]);

    if (str == NULL)
        return EXIT_ERROR;
    my_putstr(str);
    free(str);
    return EXIT_SUCCESS;
}

static char *my_array_to_str(char const **tab)
{
    char *str = malloc(sizeof(char) * word_array_len(tab));

    if (str == NULL)
        return NULL;
    str[0] = '\0';
    for (int i = 0; tab[i] != NULL; i++)
        my_strcat(str, tab[i]);
    return str;
}

static int add_alias(env_t alias, char **cmd, char *target_cmd)
{
    int exit_value;

    exit_value = my_env_add(shell->alias, cmd[1], target_cmd);
    free(target_cmd);
    return exit_value;
}

int my_alias(char **cmd, shell_t *shell)
{
    int argc = word_array_len(cmd);
    char *target_cmd;
    char *str;
    int exit_value;

    if (argc == 1) {
        my_env_display(shell->alias);
        return EXIT_SUCCESS;
    }
    if (argc == 2)
        return print_alias(cmd, shell);
    target_cmd = my_array_to_str(cmd + 2);
    if (target_cmd == NULL)
        return EXIT_ERROR;
    str = my_env_get(shell->shell);
    if (str == NULL)
        return add_alias(shell->alias, cmd, target_cmd);
    free(str);
    exit_value = my_env_update(shell->alias, cmd[1], target_cmd);
    free(target_cmd);
    return exit_value;
}