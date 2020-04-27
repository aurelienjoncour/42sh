/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** shell command function
*/

#include "minishell.h"

static int check_entry_char(char *label)
{
    if (!label) {
        return EXIT_ERROR;
    } else if (!char_is_letter(label[0]) && label[0] != '_') {
        my_putstr_error("setenv: Variable name must begin with a letter.\n");
        return EXIT_ERROR;
    }
    if (!str_is_alphanum(label)) {
        my_putstr_error("setenv: Variable name must contain alphanumeric");
        my_putstr_error(" characters.\n");
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

static int set_variable(char *label, char *value, env_t *env)
{
    bool have_entry = my_env_exist(env, label);

    if (check_entry_char(label) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    if (have_entry) {
        if (my_env_update(env, label, value) == EXIT_ERROR) {
            return EXIT_ERROR;
        }
    } else {
        if (my_env_add(env, label, value) == EXIT_ERROR) {
            return EXIT_ERROR;
        }
    }
    return EXIT_SUCCESS;
}

int my_setenv(char **cmd, minishell_t *shell)
{
    int len = word_array_len(cmd);

    if (len == 1) {
        my_env_display(&shell->env);
        shell->exit_status = SUCCESS_STATUS;
    } else if (len == 2 || len == 3) {
        if (set_variable(cmd[1], cmd[2], &shell->env)) {
            shell->exit_status = ERROR_STATUS;
            return EXIT_ERROR;
        }
        shell->exit_status = SUCCESS_STATUS;
    } else {
        my_putstr_error("setenv: Too many arguments.\n");
        shell->exit_status = ERROR_STATUS;
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
