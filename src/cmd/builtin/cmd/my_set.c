/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** shell command function
*/

#include "shell.h"

const char *ERR_BEG_LETTER = "set: Variable name must begin with "
"a letter.\n";

static const char *ERR_ALPHANUM = "set: Variable name must contain"
" alphanumeric characters.\n";

static int check_entry_char(char *label)
{
    if (!label) {
        return EXIT_ERROR;
    } else if (!char_is_letter(label[0]) && label[0] != '_') {
        my_putstr_error(ERR_BEG_LETTER);
        return EXIT_ERROR;
    }
    if (!str_is_alphanum(label)) {
        my_putstr_error(ERR_ALPHANUM);
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

static int split_parameter(const char *str, char **ptr_label,
char **ptr_value)
{
    size_t idx_separator = 0;

    for (size_t i = 1; str[i] != '\0'; i++) {
        if (str[i] == '=') {
            idx_separator = i;
            break;
        }
    }
    *ptr_label = my_strndup(str, idx_separator);
    if (!(*ptr_label))
        return EXIT_ERROR;
    if (str[idx_separator + 1] == '\0') {
        *ptr_value = NULL;
    } else {
        *ptr_value = my_strdup(&str[idx_separator + 1]);
        if (!(*ptr_value))
            return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

static int get_label_and_value(char **wa, size_t idx,
char **ptr_label, char **ptr_value)
{
    bool have_equal = false;

    for (size_t i = 0; wa[idx][i] != '\0'; i++) {
        if (wa[idx][i] == '=' && i == 0) {
            return puterr(ERR_BEG_LETTER, EXIT_ERROR);
        } else if (wa[idx][i] == '=') {
            have_equal = true;
            break;
        }
    }
    if (have_equal) {
        if (split_parameter(wa[idx], ptr_label, ptr_value) != 0)
            return EXIT_ERROR;
    } else {
        *ptr_label = my_strdup(wa[idx]);
        *ptr_value = NULL;
    }
    return EXIT_SUCCESS;
}

int set_variable_set(char **wa, size_t idx, env_t *var)
{
    bool have_entry;
    char *label = NULL;
    char *value = NULL;

    if (get_label_and_value(wa, idx, &label, &value) == EXIT_ERROR)
        return EXIT_ERROR;
    have_entry = my_env_exist(var, label);
    if (check_entry_char(label) == EXIT_ERROR) {
        return EXIT_ERROR;
    }
    if (have_entry) {
        if (my_env_update(var, label, value) == EXIT_ERROR) {
            return EXIT_ERROR;
        }
    } else {
        if (my_env_add(var, label, value) == EXIT_ERROR) {
            return EXIT_ERROR;
        }
    }
    return EXIT_SUCCESS;
}

int my_set(char **cmd, shell_t *shell)
{
    int len = 0;
    char **list = make_my_list(cmd);

    if (!list || check_cmd(cmd) == true) {
        shell->exit_status = ERROR_STATUS;
        return EXIT_SUCCESS;
    }
    if (move_in_list(list, shell, &len) == EXIT_ERROR) {
        for (size_t i = 0; list[i] != NULL; free(list[i]), i++);
        free(list);
        shell->exit_status = ERROR_STATUS;
        return EXIT_ERROR;
    }
    if (len == 0)
        my_env_display(&shell->local);
    for (size_t i = 0; list[i] != NULL; free(list[i]), i++);
    free(list);
    shell->exit_status = SUCCESS_STATUS;
    return EXIT_SUCCESS;
}
