/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-15T08:53:41+02:00 | Author: simon
*/

#include "globbing.h"

const char *ERR_NO_MATCH = "%s: No match.\n";

static const char *CHAR_GLOBBING = "*?[]";

static bool is_globbing_expr(token_t *node)
{
    if (!node || node->id != ID_WITHOUT) {
        return false;
    }
    for (size_t i = 0; node->token[i] != '\0'; i++) {
        if (my_str_have_char(CHAR_GLOBBING, node->token[i]) != -1) {
            return true;
        }
    }
    return false;
}

static void check_error(int have_success, shell_t *shell, char *cmd_name)
{
    if ((have_success & 16) == 0 && have_success != 0) {
        shell->exit_status = ERROR_STATUS;
        fprintf(stderr, ERR_NO_MATCH, cmd_name);
    }
}

static bool process_token(token_t *ptr, shell_t *shell, int *have_success,
char **cmd_name)
{
    if (is_command_name(ptr) == true) {
        *cmd_name = ptr->token;
    } else if (is_separator(ptr) == true) {
        check_error(*have_success, shell, *cmd_name);
        *cmd_name = NULL;
        *have_success = 0;
    }
    if (is_globbing_expr(ptr) == false) {
        return true;
    } else if (*cmd_name == NULL) {
        *cmd_name = ptr->token;
    }
    if (process_globbing(ptr->token) == EXIT_FAIL) {
        *have_success = *have_success | 4;
    } else {
        *have_success = *have_success | 16;
    }
    return false;
}

int globbing(cmd_t *cmd, shell_t *shell)
{
    char *cmd_name = NULL;
    int have_success = 0;

    for (token_t *ptr = cmd->begin; ptr != NULL; ptr = ptr->next) {
        if (process_token(ptr, shell, &have_success, &cmd_name)) {
            continue;
        }
    }
    check_error(have_success, shell, cmd_name);
    return EXIT_SUCCESS;
}
