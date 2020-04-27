/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** Created: 2020-03-31T15:04:50+02:00 | Author: simon
*/

#include "minishell.h"

extern const char *REDIR_PATT_IN[];
extern const char *REDIR_PATT_OUT[];

static bool check_command(cmd_t *cmd)
{
    if (have_missing_str_quote(cmd) == true) {
        return true;
    } else if (have_missing_name_redirection(cmd) == true) {
        return true;
    }
    if (have_several_redirection(cmd) == true) {
        return true;
    } else if (have_null_command(cmd) == true) {
        return true;
    }
    return false;
}

static void get_redirect_mode(cmd_t *cmd)
{
    for (size_t i = 0; REDIR_PATT_IN[i] != NULL; i++) {
        if (!cmd->redirect_in || !cmd->redirect_in[0]) {
            break;
        } else if (my_strcmp(REDIR_PATT_IN[i], cmd->redirect_in[0]) == 0) {
            cmd->red_mode_in = i;
        }
    }
    for (size_t i = 0; REDIR_PATT_OUT[i] != NULL; i++) {
        if (!cmd->redirect_out || !cmd->redirect_out[0]) {
            break;
        } else if (my_strcmp(REDIR_PATT_OUT[i], cmd->redirect_out[0]) == 0) {
            cmd->red_mode_out = i;
        }
    }
}

void command_parse(cmd_t *cmd)
{
    cmd->formatted = command_format(cmd->command);
    if (cmd->formatted == NULL) {
        cmd->err = true;
        return;
    }
    cmd->wa = command_to_word_array(cmd->formatted);
    if (!cmd->wa) {
        cmd->err = true;
        return;
    }
    if (check_command(cmd) == true) {
        cmd->err= true;
        return;
    }
    if (cmd_split_word_array(cmd) == EXIT_ERROR) {
        cmd->err = true;
        return;
    }
    get_redirect_mode(cmd);
}
