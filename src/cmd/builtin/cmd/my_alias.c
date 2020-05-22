/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** shell command function
*/

#include <unistd.h>
#include <stdbool.h>
#include "my.h"
#include "shell.h"

static int print_alias(char *label, shell_t *shell, bool print_label)
{
    char *str = my_env_get_value(&shell->alias, label);

    shell->exit_status = SUCCESS_STATUS;
    if (str == NULL)
        return EXIT_SUCCESS;
    if (print_label) {
        my_putstr(label);
        my_putstr("\t");
        free(label);
    }
    if (str[0] == '(') {
        str[my_strlen(str) - 1] = '\0';
        my_putstr(str + 1);
    } else
        my_putstr(str);
    my_putstr("\n");
    free(str);
    return EXIT_SUCCESS;
}

static int set_alias(shell_t *shell, const char *label, char *target_cmd,
                    bool update)
{
    int exit_value;

    if (update)
        exit_value = my_env_update(&shell->alias, label, target_cmd);
    else {
        if (!my_strcmp(label, "unalias") || !my_strcmp(label, "alias")) {
            shell->exit_status = ERROR_STATUS;
            free(target_cmd);
            my_putstr_error(label);
            return my_puterror(": Too dangerous to alias that.\n",
                                EXIT_FAILURE);
        }
        exit_value = my_env_add(&shell->alias, label, target_cmd);
    }
    free(target_cmd);
    shell->exit_status = exit_value;
    return exit_value;
}

static bool get_alias_opt(char **argv)
{
    static char *print = NULL;

    if (argv[1][0] != '-')
        return false;
    for (int i = 1; argv[1][i] != '\0'; i++)
        if (argv[1][i] != 'p')
            return true;
    if (argv[2] == NULL && print != NULL)
        printf("%s\n", print);
    else if (argv[2] != NULL)
        print = my_array_to_str(argv + 2, false);
    return true;
}

int my_alias(char **cmd, shell_t *shell)
{
    int argc = word_array_len(cmd);
    char *target_cmd;

    if (argc > 1 && get_alias_opt(cmd))
        return EXIT_SUCCESS;
    if (argc == 1) {
        for (int i = 0; i < shell->alias.size; i++)
            print_alias(my_env_get_var_label(shell->alias.var[i]),
                        shell, true);
        return EXIT_SUCCESS;
    }
    if (argc == 2)
        return print_alias(cmd[1], shell, false);
    target_cmd = my_array_to_str(cmd + 2, true);
    if (target_cmd == NULL)
        return EXIT_ERROR;
    if (my_env_exist(&shell->alias, cmd[1]))
        return set_alias(shell, cmd[1], target_cmd, true);
    return set_alias(shell, cmd[1], target_cmd, false);
}