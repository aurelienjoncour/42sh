/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-02T16:00:49+02:00 | Author: simon
*/

#include "shell.h"

static const char *ENTRY_CHAR_IGNORE = " \t";

static bool process_check_entry(char *entry, shell_t *shell,
char **sub_entries)
{
    for (size_t i = 0; sub_entries[i] != NULL; i++) {
        if (check_sub_entry(sub_entries[i]) == true) {
            shell->exit_status = ERROR_STATUS;
            free(entry);
            word_array_destroy(sub_entries);
            return true;
        }
    }
    return false;
}

int minishell_exec(shell_t *shell, char *entry)
{
    char **sub_entries  = split_entry(entry);

    if (process_check_entry(entry, shell, sub_entries)) {
        return EXIT_SUCCESS;
    }
    free(entry);
    if (!sub_entries)
        return EXIT_ERROR;
    for (size_t i = 0; sub_entries[i] != NULL; i++) {
        if (str_have_only_chars(sub_entries[i], ENTRY_CHAR_IGNORE) == true) {
            continue;
        }
        if (minishell_exec_piped(shell, sub_entries[i]) != EXIT_SUCCESS) {
            return EXIT_ERROR;
        }
    }
    word_array_destroy(sub_entries);
    return EXIT_SUCCESS;
}
