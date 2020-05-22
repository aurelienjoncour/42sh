/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** check_interval
*/

#include "shell.h"

bool check_interval(interval_t *interval, const char *filename, size_t *c_fil)
{
    bool ret = false;

    if ((interval->c[1] - interval->c[0]) > -1) {
        for (char c = interval->c[0]; c <= interval->c[1]; c++) {
            if (c == filename[*c_fil])
                return true;
        }
    }
    if (interval->next != NULL)
        ret = check_interval(interval->next, filename, c_fil);
    return ret;
}