/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** Created: 2020-04-08T10:23:42+02:00 | Author: simon
*/

#include "minishell.h"

extern const char *REDIR_PATT_IN[];
extern const char *REDIR_PATT_OUT[];

static void get_redirection_idx(cmd_t *cmd, int *idx_in, int *idx_out)
{
    int len = word_array_len(cmd->wa);

    for (size_t i = 0; REDIR_PATT_IN[i] != NULL; i++) {
        *idx_in = word_array_search(cmd->wa, len, REDIR_PATT_IN[i]);
        if (*idx_in != -1) {
            break;
        }
    }
    for (size_t i = 0; REDIR_PATT_OUT[i] != NULL; i++) {
        *idx_out = word_array_search(cmd->wa, len, REDIR_PATT_OUT[i]);
        if (*idx_out != -1) {
            break;
        }
    }
}

static int alloc_cmd(cmd_t *cmd, int size)
{
    cmd->cmd = malloc(sizeof(char *) * (size + 1));
    if (!cmd->cmd)
        return EXIT_ERROR;
    for (ssize_t i = 0; i < (size + 1); i++)
        cmd->cmd[i] = NULL;
    return EXIT_SUCCESS;
}

static int alloc_redirect(int idx_redir, char ***dest, int *size)
{
    if (idx_redir != -1) {
        *dest = malloc(sizeof(char *) * 3);
        if (!(*dest)) {
            return EXIT_ERROR;
        }
        for (size_t i = 0; i < 3; i++)
            (*dest)[i] = NULL;
        (*size) -= 2;
    }
    return EXIT_SUCCESS;
}

static void fill_word_array(cmd_t *cmd, int idx_redir_in, int idx_redir_out)
{
    size_t idx_cmd = 0;
    size_t redir_in_idx = 0;
    size_t redir_out_idx = 0;

    for (size_t i = 0; cmd->wa[i] != NULL; i++) {
        if (idx_redir_in != -1 && ((int)i == idx_redir_in
                || (int)i == (idx_redir_in + 1))) {
            cmd->redirect_in[redir_in_idx++] = cmd->wa[i];
        } else if (idx_redir_out != -1 && ((int)i == idx_redir_out
                || (int)i == (idx_redir_out + 1))) {
            cmd->redirect_out[redir_out_idx++] = cmd->wa[i];
        } else {
            cmd->cmd[idx_cmd++] = cmd->wa[i];
        }
    }
    if (idx_redir_in != -1)
        cmd->redirect_in[redir_in_idx] = NULL;
    if (idx_redir_out != -1)
        cmd->redirect_out[redir_out_idx] = NULL;
    cmd->cmd[idx_cmd] = NULL;
}

int cmd_split_word_array(cmd_t *cmd)
{
    int size = word_array_len(cmd->wa);
    int idx_redir_in;
    int idx_redir_out;

    if (!cmd->wa) {
        return EXIT_ERROR;
    }
    get_redirection_idx(cmd, &idx_redir_in, &idx_redir_out);
    if (alloc_redirect(idx_redir_in, &cmd->redirect_in, &size) != 0) {
        return puterr("cmd split wa : malloc err\n", EXIT_ERROR);
    }
    if (alloc_redirect(idx_redir_out, &cmd->redirect_out, &size) != 0) {
        return puterr("cmd split wa : malloc err\n", EXIT_ERROR);
    }
    if (alloc_cmd(cmd, size) == EXIT_ERROR) {
        return puterr("cmd split wa : malloc err\n", EXIT_ERROR);
    }
    fill_word_array(cmd, idx_redir_in, idx_redir_out);
    return EXIT_SUCCESS;
}
