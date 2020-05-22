/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** main function
*/

#include "shell.h"

int main(int argc, char **argv, char **env)
{
    shell_t shell;
    int ret;
    char *shell_script = NULL;

    if (argc == 2) {
        shell_script = argv[1];
    }
    if (shell_create(&shell, env, shell_script) == EXIT_ERROR) {
        return EXIT_ERROR;
    } else {
        if (load_argv(&shell, argv) == EXIT_ERROR) {
            return EXIT_ERROR;
        }
        ret = shell_run(&shell);
        shell_destroy(&shell);
        return ret;
    }
}
