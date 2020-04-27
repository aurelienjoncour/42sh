/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** tool function
*/

#include "minishell.h"

bool char_is_letter(const char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return true;
    }
    return false;
}

bool str_is_alphanum(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] != '_' && (str[i] < '0' || str[i] > '9')
                && !char_is_letter(str[i])) {
            return false;
        }
    }
    return true;
}

bool have_slash(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '/') {
            return true;
        }
    }
    return false;
}

bool str_have_only_chars(const char *str, const char *chars)
{
    if (!str || !chars)
        return false;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (my_str_have_char(chars, str[i]) == -1) {
            return false;
        }
    }
    return true;
}

bool word_array_have_empty_str(char **warray)
{
    for (size_t i = 0; warray[i] != NULL; i++) {
        if (str_have_only_chars(warray[i], " \t") == true) {
            return true;
        }
    }
    return false;
}
