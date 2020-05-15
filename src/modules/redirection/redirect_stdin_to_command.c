/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-13T17:34:58+02:00 | Author: simon
*/

#include "shell.h"

static char *get_line_stdin(void)
{
    ssize_t n_read;
    size_t size = 0;
    char *ret = NULL;

    n_read = getline(&ret, &size, stdin);
    if (n_read == -1) {
        free(ret);
        return NULL;
    }
    return ret;
}

static void show_prompt(void)
{
    if (isatty(STDIN_FILENO)) {
        write(STDOUT_FILENO, "? ", 2);
    }
}

static char *read_stdin(const char *pattern_stop)
{
    char *line = NULL;
    char *data = NULL;
    char *data_temp;

    if (!pattern_stop)
        return NULL;
    do {
        show_prompt();
        line = get_line_stdin();
        if (line && my_strncmp(pattern_stop, line, my_strlen(line) - 1) == 0) {
            free(line);
            break;
        } else if (line != NULL) {
            data_temp = my_str_concat(data, line);
            free(data);
            free(line);
            data = data_temp;
        }
    } while (line != NULL && data != NULL);
    return data;
}

int redirect_stdin_to_command(redirect_t *redirect)
{
    char *data = NULL;
    int len_data;

    if (pipe(redirect->pipe_redirect) == -1) {
        return puterr("pipe : fail\n", EXIT_ERROR);
    }
    data = read_stdin(redirect->string_left);
    if (data) {
        len_data = my_strlen(data);
        write(redirect->pipe_redirect[1], data, len_data);
        free(data);
    }
    if (close(redirect->pipe_redirect[1]) == -1) {
        return puterr("close pipe_red[1] : fail\n", EXIT_ERROR);
    }
    if (dup2(redirect->pipe_redirect[0], 0) == -1) {
        return puterr("dup2 : fail\n", EXIT_ERROR);
    }
    return EXIT_SUCCESS;
}
