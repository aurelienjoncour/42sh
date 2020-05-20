/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-18T10:21:27+02:00 | Author: simon
*/

#include "shell.h"

static const char *ERR_ALIAS_LOOP = "Alias loop.\n";

static int process_alias_check_token(shell_t *shell, cmd_t *cmd,
bool *have_alias)
{
    token_t *cpy_ptr;
    int ret;
    bool is_cmd = is_command_name(ptr);

    if (is_cmd == true) {
        cpy_ptr = ptr;
        ptr = ptr->next;
        ret = try_subst_alias(cmd, cpy_ptr, shell);
    }
    if (is_cmd == true && ret == EXIT_ERROR) {
        return EXIT_ERROR;
    } else if (is_cmd == false) {
        ptr = ptr->next;
    }
    if (is_cmd == true && ret == EXIT_SUCCESS) {
        *have_alias = true;
    }
    return EXIT_SUCCESS;
}

static int process_alias(shell_t *shell, cmd_t *cmd, size_t idx)
{
    bool have_alias = false;

    for (token_t *ptr = cmd->begin; ptr != NULL;) {
        if (process_alias_check_token(shell, cmd, &have_alias) == EXIT_ERROR) {
            return EXIT_ERROR;
        }
    }
    if (idx > 6) {
        my_putstr_error(ERR_ALIAS_LOOP);
        return EXIT_ERROR;
    }
    if (have_alias == true) {
        return process_alias(shell, cmd, ++idx);
    }
    return EXIT_SUCCESS;
}

int substr_variables(shell_t *shell, cmd_t *cmd)
{
    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (try_subst_variable(ptr, shell) == EXIT_ERROR) {
            return EXIT_FAIL;
        }
    }
    if (process_alias(shell, cmd, 0) == EXIT_ERROR) {
        return EXIT_FAIL;
    }
    return EXIT_SUCCESS;
}
