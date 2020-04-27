/*
** EPITECH PROJECT, 2020
** PROJECT_NAME
** File description:
** Created: 2020-04-13T11:15:30+02:00 | Author: simon
*/

#include "my.h"

void my_str_count_char_suite(const char *str, const char c,
int *occur, int *serie)
{
    int curr_serie = 0;

    *occur = 0;
    *serie = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            *occur += 1;
            curr_serie++;
        } else if (curr_serie > *serie) {
            *serie = curr_serie;
            curr_serie = 0;
        } else {
            curr_serie = 0;
        }
    }
}
