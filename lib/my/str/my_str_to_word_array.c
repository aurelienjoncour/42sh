/*
** EPITECH PROJECT, 2019
** CPool_Day08_2019
** File description:
** Task04
*/

#include "my.h"

static bool is_char_in_str(const char c, const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (c == str[i])
            return true;
    }
    return false;
}

static int get_next_idx_delim(const char *str, const char *delim,
const int begin)
{
    int idx = -1;

    for (size_t i = begin; str[i] != '\0'; i++) {
        if (is_char_in_str(str[i], delim)) {
            idx = i;
            break;
        }
    }
    if (idx == -1)
        idx = my_strlen(str);
    return idx;
}

static int count_word(const char *str, const char *delim)
{
    int nb_word = 1;

    if (str[0] == '\0')
        return 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (is_char_in_str(str[i], delim))
            nb_word++;
    }
    return nb_word;
}

static int create_words(const char *str, const char *delim, char ***ret,
const int nb_word)
{
    int prev_idx = 0;
    int idx_delim = 0;

    for (size_t i = 0; i < (size_t)nb_word; i++) {
        idx_delim = get_next_idx_delim(str, delim, prev_idx);
        (*ret)[i] = malloc(sizeof(char) * (idx_delim - prev_idx + 1));
        if (!(*ret)[i])
            return EXIT_FAILURE;
        my_strncpy((*ret)[i], str + prev_idx, idx_delim - prev_idx);
        (*ret)[i][idx_delim - prev_idx] = '\0';
        prev_idx = idx_delim + 1;
    }
    return EXIT_SUCCESS;
}

char **my_str_to_word_array(const char *str, const char *delim)
{
    int nb_word = count_word(str, delim);
    char **ret = NULL;

    if (!str || !delim || delim[0] == '\0')
        return NULL;
    ret = malloc(sizeof(char *) * (1 + nb_word));
    if (!ret)
        return NULL;
    if (nb_word == 0) {
        ret[0] = NULL;
        return ret;
    }
    ret[nb_word] = NULL;
    if (create_words(str, delim, &ret, nb_word) == EXIT_FAILURE)
        return NULL;
    return ret;
}
