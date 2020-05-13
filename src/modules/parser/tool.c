/*
** EPITECH PROJECT, 2020
** parser
** File description:
** tokeniser
*/

#include <stdlib.h>
#include <string.h>
#include "parser_t.h"
#include "parser.h"

extern const parser_t DELIMIT[];

char *my_strncat_realloc(char *s1, char *s2, size_t n)
{
    size_t len_s1 = strlen(s1);
    char *result = malloc(sizeof(char) * (len_s1 + n + 1));

    if (result == NULL)
        return NULL;
    strcpy(result, s1);
    strncat(result, s2, n);
    free(s1);
    return result;
}

ssize_t is_special_id(char *str, size_t cursor[2])
{
    size_t len_delimit;

    for (ssize_t i = 0; DELIMIT[i].start != 0; i++) {
        len_delimit = strlen(DELIMIT[i].start);
        if (!strncmp(DELIMIT[i].start, str+cursor[1], len_delimit)) {
            return i;
        }
    }
    return -1;
}
