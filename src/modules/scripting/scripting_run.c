/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-08T15:35:23+02:00 | Author: simon
*/

#include "shell.h"

int shell_scripting_run(shell_t *shell)
{
    char **content = my_read_file(shell->shell_script);

    if (!content) {
        return ERROR_STATUS;
    }
    my_show_word_array(content);
    word_array_destroy(content);
    return shell->exit_status;
}
