/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** Created: 2020-04-15T17:49:09+02:00 | Author: simon
*/

#include "shell.h"

static const char PIPE_CHAR = '|';

static const char *REDIRECT_PATT[] =
{
    "<",
    "<<",
    ">>",
    ">",
    NULL
};

static const int NO_TYPE = 0;
static const int TYPE_IN = 1;
static const int TYPE_OUT = 2;

static const char *ERR_AMBIG_IN = "Ambiguous input redirect.\n";
static const char *ERR_AMBIG_OUT = "Ambiguous output redirect.\n";

static int get_type_redirect_pattern(const char *str)
{
    int res;

    for (size_t i = 0; REDIRECT_PATT[i] != NULL; i++) {
        res = my_strncmp(REDIRECT_PATT[i], str, my_strlen(REDIRECT_PATT[i]));
        if (res == 0 && i <= 1) {
            return TYPE_IN;
        } else if (res == 0) {
            return TYPE_OUT;
        }
    }
    return NO_TYPE;
}

static int count_pipe(const char *sub_entry)
{
    int count = 0;

    for (size_t i = 0; sub_entry[i] != '\0'; i++) {
        if (sub_entry[i] == PIPE_CHAR) {
            count++;
        }
    }
    return count;
}

bool check_position_redirection_in_pipe(const char *sub_entry)
{
    int max_nb_pipe = count_pipe(sub_entry);
    int type;
    int nb_pipe = 0;

    for (size_t i = 0; sub_entry[i] != '\0'; i++) {
        if (sub_entry[i] == PIPE_CHAR) {
            nb_pipe++;
            continue;
        }
        type = get_type_redirect_pattern(&sub_entry[i]);
        if (type == TYPE_IN && nb_pipe > 0) {
            my_putstr_error(ERR_AMBIG_IN);
            return true;
        } else if (type == TYPE_OUT && nb_pipe != max_nb_pipe) {
            my_putstr_error(ERR_AMBIG_OUT);
            return true;
        }
    }
    return false;
}
