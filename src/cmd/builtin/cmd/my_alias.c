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

static char *my_array_to_str(char **tab)
{
    int size = 0;
    char *str;

    for (int i = 0; tab[i] != NULL; i++)
        size += my_strlen(tab[i]);
    str = malloc(sizeof(char) * size);
    if (str == NULL)
        return NULL;
    str[0] = '\0';
    for (int i = 0; tab[i] != NULL; i++)
        my_strcat(str, tab[i]);
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

static bool get_alias_opt(int argc, char * const *argv)
{
    static char *print = NULL;
    int opt;
    char *arg = "NULL";

    do {
        opt = getopt(argc, argv, "p::");
        if (opt == '?')
            return true;
        if (opt == 'p')
            arg = my_strdup(optarg);
    } while (opt != -1);
    if (arg != NULL && !my_strcmp(arg, "NULL"))
        return false;
    if (arg == NULL && print != NULL)
        printf("%s\n", print);
    else if (arg) {
        free(print);
        print = arg;
    }
    return true;
}

int my_alias(char **cmd, shell_t *shell)
{
    int argc = word_array_len(cmd);
    char *target_cmd;

    if (get_alias_opt(argc, cmd))
        return EXIT_SUCCESS;
    if (argc == 1) {
        for (int i = 0; i < shell->alias.size; i++)
            print_alias(my_env_get_var_label(shell->alias.var[i]),
                        &shell->alias, true);
        return EXIT_SUCCESS;
    }
    if (argc == 2)
        return print_alias(cmd[1], &shell->alias, false);
    target_cmd = my_array_to_str(cmd + 2);
    if (target_cmd == NULL)
        return EXIT_ERROR;
    if (my_env_exist(&shell->alias, cmd[1]))
        return set_alias(&shell->alias, cmd[1], target_cmd, true);
    return set_alias(&shell->alias, cmd[1], target_cmd, false);
}