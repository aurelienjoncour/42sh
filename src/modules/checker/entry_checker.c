/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-11T13:19:19+02:00 | Author: simon
*/

#include "shell.h"

bool is_separator(token_t *ptr)
{
    if (ptr->type == D_SEPARATOR || ptr->id == ID_PIPE) {
        return true;
    }
    return false;
}

bool is_text_token(token_t *ptr, bool include_parenthesis)
{
    if ((ptr->id == ID_WITHOUT
            && (!ptr->prev || !is_redirection(ptr->prev->id)))
            || (ptr->type == D_DELIM && ptr->id != ID_PARENTHESE)) {
        return true;
    } else if (include_parenthesis == true && ptr->id == ID_PARENTHESE) {
        return true;
    }
    return false;
}

static bool is_null_cmd(cmd_t *cmd)
{
    if (!cmd || !cmd->begin) {
        return true;
    }
    if ((cmd->begin)->token == NULL) {
        return true;
    }
    return false;
}

static int call_check_function(cmd_t *cmd, const char *entry)
{
    if (have_missing_str_quote(entry) == true) {
        return EXIT_ERROR;
    } else if (check_parenthesis(cmd)) {
        return EXIT_ERROR;
    }
    if (have_missing_name_redirection(cmd) == true) {
        return EXIT_ERROR;
    }
    if (check_position_redirection_in_pipe(cmd) == true) {
        return EXIT_ERROR;
    }
    if (have_several_redirection(cmd) == true) {
        return EXIT_ERROR;
    } else if (have_null_command(cmd) == true) {
        return EXIT_ERROR;
    }
    if (check_have_empty_pipe(cmd) == true) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

int entry_checker(shell_t *shell, cmd_t *cmd, const char *entry)
{
    if (!cmd || !cmd->begin) {
        return puterr("Entry checker: null cmd.\n", EXIT_ERROR);
    }
    if (is_null_cmd(cmd) == true) {
        return puterr("Entry checker: null cmd.\n", EXIT_ERROR);
    }
    if (call_check_function(cmd, entry) == EXIT_ERROR) {
        shell->exit_status = ERROR_STATUS;
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
