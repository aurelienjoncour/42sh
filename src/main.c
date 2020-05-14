/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** main function
*/

#include "shell.h"

int main(__attribute((unused))int argc, __attribute((unused))char **argv,
    char **env)
{
    shell_t shell;
    int ret;

    if (shell_create(&shell, env)) {
        return EXIT_ERROR;
    } else {
        ret = shell_run(&shell);
        shell_destroy(&shell);
        return ret;
    }
}
