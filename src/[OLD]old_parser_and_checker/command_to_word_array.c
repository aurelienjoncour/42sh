/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** Created: 2020-04-03T10:47:38+02:00 | Author: simon
*/

#include "shell.h"

extern const int TYPE_WORD;
extern const int TYPE_REDIR;
extern const int TYPE_SPACE;
extern const int TYPE_DELIM_A;
extern const int TYPE_DELIM_B;

extern const char BREAK;

//   # Word Delim:
//        => idx_begin : idx of the first char of the word.
//        => idx end : idx of the (last char + 1) of the word.

static int count_word(const char *str)
{
    int nb_word = 0;
    size_t idx = 0;

    if (!str)
        return 0;
    while (str[idx] == BREAK)
        idx++;
    if (str[0] == '\0')
        return 0;
    for (;str[idx] != '\0'; idx++) {
        if (idx > 0 && str[idx - 1] == BREAK && str[idx] != BREAK) {
            nb_word++;
        } else if (idx == 0 && str[idx] != BREAK) {
            nb_word++;
        }
    }
    return nb_word;
}

static void get_next_idx_end_begin(const char *str, size_t *begin, size_t *end)
{
    while (str[*begin] == BREAK)
        (*begin)++;
    *end = (*begin + 1);
    while (str[*end] != '\0' && str[*end] != BREAK) {
        (*end)++;
    }
}

static int create_words(const char *str, char ***ret, const int nb_word)
{
    size_t idx_begin = 0;
    size_t idx_end = 0;

    for (size_t i = 0; i < (size_t)nb_word; i++) {
        get_next_idx_end_begin(str, &idx_begin, &idx_end);
        (*ret)[i] = malloc(sizeof(char) * (idx_end - idx_begin + 1));
        if (!(*ret)[i])
            return EXIT_FAILURE;
        my_strncpy((*ret)[i], str + idx_begin, idx_end - idx_begin);
        (*ret)[i][idx_end - idx_begin] = '\0';
        idx_begin = idx_end;
    }
    return EXIT_SUCCESS;
}

char **command_to_word_array(const char *formatted)
{
    int nb_word = count_word(formatted);
    char **ret = NULL;

    if (!formatted)
        return NULL;
    ret = malloc(sizeof(char *) * (1 + nb_word));
    if (!ret)
        return NULL;
    if (nb_word == 0) {
        ret[0] = NULL;
        return ret;
    }
    ret[nb_word] = NULL;
    if (create_words(formatted, &ret, nb_word) == EXIT_FAILURE)
        return NULL;
    return ret;
}
