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

int shell_exec(shell_t *shell, char *entry)
{
    // TODO : fredou parser (+ cleaner)

    // TODO : substitute variables

    // TODO : entry checker (error)

    free(entry);
    return EXIT_SUCCESS;
}
