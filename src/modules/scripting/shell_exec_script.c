/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-08T15:35:23+02:00 | Author: simon
*/

#include "shell.h"

int shell_exec_script(shell_t *shell, cmd_t *boolop_cmd)
{
    // TODO : CHECK => have script ?
    // TODO : CHECK => script struct not finish ?
    //         |> call getline to read file stdin content.

    // TODO : if/else eval

    // TODO : while + foreach eval

    // call :: cmd_process function
    if (cmd_process(shell, boolop_cmd) != EXIT_SUCCESS) {
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
