/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-04-02T15:59:37+02:00 | Author: simon
*/

#include "shell.h"

char **split_entry(char *entry)
{
    return my_str_to_word_array(entry, ";");
}
