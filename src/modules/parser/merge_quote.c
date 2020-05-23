/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-20T17:14:11+02:00 | Author: simon
*/

#include "my.h"
#include "parser.h"
#include <string.h>

static bool merge_quote(char *entry, size_t idx_first)
{
    size_t size = (strlen(entry) - 2);
    char *dup = my_strdup(&entry[idx_first + 2]);

    if (!dup) {
        return true;
    }
    if ((entry[idx_first + 2]) == '\0') {
        entry[idx_first] = '\0';
    } else {
        strcpy(&entry[idx_first], dup);
        entry[size] = '\0';
    }
    free(dup);
    return false;
}

int parser_merge_quote(char *entry)
{
    bool ret = true;

    for (size_t i = 0; entry[i] != '\0'; i++) {
        if (char_is_quote(entry, i)
                && (entry[i] == entry[i + 1])) {
            ret = merge_quote(entry, i);
        }
        if (ret == false) {
            return parser_merge_quote(entry);
        }
    }
    return EXIT_SUCCESS;
}
