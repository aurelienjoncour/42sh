/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-18T11:08:45+02:00 | Author: simon
*/

#ifndef SUBST_VAR_H
#define SUBST_VAR_H

int try_subst_alias(cmd_t *cmd, token_t *tok, shell_t *shell);

int try_subst_variable(token_t *tok, shell_t *shell);

int process_subst_value(char *label, token_t *tok, env_t *var, size_t idx);

// MAIN FUNCTIONS
int substr_variables(shell_t *shell, cmd_t *cmd);

#endif
