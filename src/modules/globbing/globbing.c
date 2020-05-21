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

static bool check_error(int have_success, shell_t *shell, char *cmd_name)
{
    if ((have_success & 16) == 0 && have_success != 0) {
        shell->exit_status = ERROR_STATUS;
        fprintf(stderr, ERR_NO_MATCH, cmd_name);
        return true;
    }
    return false;
}

static int process_token(token_t **ptr, cmd_t *cmd, char **cmd_name)
{
    token_t *save_ptr = *ptr;

    if (is_command_name(save_ptr) == true) {
        *cmd_name = save_ptr->token;
    }
    if (is_globbing_expr(save_ptr) == false) {
        return 2;
    } else if (*cmd_name == NULL) {
        *cmd_name = save_ptr->token;
    }
    *ptr = (*ptr)->next;
    if (process_globbing(save_ptr, cmd) == EXIT_FAIL) {
        return 4;
    } else {
        return 16;
    }
}

int globbing(cmd_t *cmd, shell_t *shell)
{
    char *cmd_name = NULL;
    int have_success = 0;
    int ret = 0;

    for (token_t *ptr = cmd->begin; ptr != NULL;) {
        ret = process_token(&ptr, cmd, &cmd_name);
        if (ret == 2) {
            ptr = ptr->next;
            continue;
        } else if (ret == 16 || ret == 4) {
            have_success = have_success | ret;
        }
    }
    if (check_error(have_success, shell, cmd_name)) {
        return EXIT_FAIL;
    }
    return EXIT_SUCCESS;
}
