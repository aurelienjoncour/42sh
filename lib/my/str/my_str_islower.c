/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** task14
*/

#include <stdbool.h>
#include <stddef.h>

bool my_str_islower(char const *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] > 'z' || str[i] < 'a')
            return false;
    }
    return true;
}
