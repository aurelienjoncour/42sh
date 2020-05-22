/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-18T10:21:27+02:00 | Author: simon
*/

#include "shell.h"

static const char *ERR_VAR_NAME = "Illegal variable name.\n";

static const char *ERR_NEWLINE = "Newline in variable name.\n";
static const char *ERR_MISSING_BRACKET = "Missing '}'.\n";

static bool is_valid_var_char(const char c)
{
    if (char_is_letter(c) || (c >= '0' && c <= '9') || c == '_') {
        return true;
    }
    return false;
}

static bool check_bracket_var(const char *str)
{
    if (str[1] == '\0') {
        my_putstr_error(ERR_NEWLINE);
        return true;
    } else if (strncmp(str, "{?}", 3) == 0)
        return false;
    if (is_valid_var_char(str[1]) == false) {
        my_putstr_error(ERR_VAR_NAME);
        return true;
    }
    if (str[2] == '\0') {
        my_putstr_error(ERR_MISSING_BRACKET);
        return true;
    }
    for (size_t i = 2; str[i] != '}' && str[i] != '\0'; i++) {
        if (is_valid_var_char(str[i]) == false) {
            my_putstr_error(ERR_MISSING_BRACKET);
            return true;
        }
    }
    return false;
}

static bool check_standard_var(const char *str)
{
    if (strncmp(str, "?", 1) == 0 && is_valid_var_char(str[1]) == false) {
        return false;
    }
    if (is_valid_var_char(str[0]) == true) {
        return false;
    }
    return true;
}

int check_variable_name(char *str)
{
    if (str == NULL || str[0] == '\0') {
        return EXIT_SUCCESS;
    }
    if (str[0] == ' ' || str[0] == '\t') {
        return EXIT_FAIL;
    }
    if (str[0] == '{' && check_bracket_var(str) == true) {
        return EXIT_ERROR;
    } else if (str[0] != '{' && check_standard_var(str) == true) {
        my_putstr_error(ERR_VAR_NAME);
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
