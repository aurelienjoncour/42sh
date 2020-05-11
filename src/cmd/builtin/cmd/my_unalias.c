/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** shell command function
*/

#include "my.h"

int my_unalias(char **cmd, shell_t *shell)
{
    if (word_array_len(cmd) <= 1) {
        my_puterror("unalias: Too few arguments.\n")
        return EXIT_FAILURE;
    }
    for (int i = 1; cmd[i] != NULL; i++)
        my_env_rm(&shell->alias, cmd[i]);
    return EXIT_SUCCESS;
}