/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** shell command function
*/

#include "my.h"
#include "shell_t.h"

int my_unalias(char **cmd, shell_t *shell)
{
    if (word_array_len(cmd) <= 1)
        return my_puterror("unalias: Too few arguments.\n", EXIT_FAILURE);
    for (int i = 1; cmd[i] != NULL; i++) {
        if (cmd[i][0] == '-')
            continue;
        my_env_rm(&shell->alias, cmd[i]);
    }
    return EXIT_SUCCESS;
}