/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** shell command function
*/

#include <unistd.h>
#include <stdbool.h>
#include "my.h"
#include "shell_t.h"

static int print_alias(char *label, env_t *alias, bool print_label)
{
    char *str = my_env_get_value(alias, label);

    if (str == NULL)
        return EXIT_SUCCESS;
    if (print_label) {
        my_putstr(label);
        my_putstr("\t");
        free(label);
    }
    my_putstr(str);
    my_putstr("\n");
    free(str);
    return EXIT_SUCCESS;
}

static char *my_array_to_str(char **tab, bool parent)
{
    int size = 0;
    char *str;
    int i_tab = 0;

    for (; tab[i_tab] != NULL; i_tab++)
        size += my_strlen(tab[i_tab]) + 1;
    str = malloc(sizeof(char) * size + 1 + (i_tab > 1 ? 2 : 0));
    if (str == NULL)
        return NULL;
    if (i_tab > 1 && parent)
        str[1] = '\0';
    str[0] = i_tab > 1 && parent ? '(' : '\0';
    for (int i = 0; tab[i] != NULL; i++) {
        my_strcat(str, tab[i]);
        my_strcat(str, " ");
    }
    str[my_strlen(str) - 1] = '\0';
    if (i_tab > 1 && parent)
        my_strcat(str, ")");
    return str;
}

static int set_alias(env_t *alias, const char *label, char *target_cmd,
                    bool update)
{
    int exit_value;

    if (update)
        exit_value = my_env_update(alias, label, target_cmd);
    else {
        if (!my_strcmp(label, "unalias")) {
            free(target_cmd);
            return my_puterror("unalias: Too dangerous to alias that.\n",
                                EXIT_FAILURE);
        }
        exit_value = my_env_add(alias, label, target_cmd);
    }
    free(target_cmd);
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
                        &shell->alias, true);
        return EXIT_SUCCESS;
    }
    if (argc == 2)
        return print_alias(cmd[1], &shell->alias, false);
    target_cmd = my_array_to_str(cmd + 2, true);
    if (target_cmd == NULL)
        return EXIT_ERROR;
    if (my_env_exist(&shell->alias, cmd[1]))
        return set_alias(&shell->alias, cmd[1], target_cmd, true);
    return set_alias(&shell->alias, cmd[1], target_cmd, false);
}