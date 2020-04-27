/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** Task12
*/

#include <stdbool.h>
#include <stddef.h>

bool my_str_isalpha(char const *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z') {
            return false;
        }
    }
    return true;
}
