/*
** EPITECH PROJECT, 2019
** 45sh
** File description:
** 46sh
*/

#include "shell.h"

bool ctrl_d_manage(int ch, shell_t *shell, char *line, size_t *pos)
{
    if (ch == 4) {
        if (line && line[0] == '\0')
            free(line);
        if (!line || line[0] == '\0') {
            return true;
        }
        else if (*pos == strlen(line)) {
            fprintf(stdout, "\n");
            display_line(shell, line, *pos);
        }
        else {
            rm_char(line, pos, true);
        }
    }
    return false;
}
