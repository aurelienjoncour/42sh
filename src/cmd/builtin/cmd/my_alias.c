/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** shell command function
*/

#include "my.h"

static int print_alias(char *label, shell_t *shell)
{
    char *str = my_env_get_value(shell->alias, label);

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

static int set_alias(env_t *alias, const char *label, const char *target_cmd,
        int (*func)(env_t *alias, const char *label, const char *target_cmd))
{
    int exit_value

    if (!my_strcmp(label, "unalias")) {
        free(target_cmd);
        my_puterror("unalias: Too dangerous to alias that.\n");
        return EXIT_FAILURE;
    }
    exit_value = func(alias, label, target_cmd);
    free(target_cmd);
    return exit_value;
}

int my_alias(char **cmd, shell_t *shell)
{
    int argc = word_array_len(cmd);
    char *target_cmd;

    if (argc == 1) {
        my_env_display(shell->alias);
        return EXIT_SUCCESS;
    }
    if (argc == 2)
        return print_alias(cmd[1], shell);
    target_cmd = my_array_to_str(cmd + 2);
    if (target_cmd == NULL)
        return EXIT_ERROR;
    if (my_env_exist(&shell->alias, cmd[1]))
        return update_alias(&shell->alias, cmd[1], target_cmd, &my_env_update);
    return add_alias(&shell->alias, cmd[1], target_cmd, &my_env_add);
}