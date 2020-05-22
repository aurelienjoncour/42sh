/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** process_bracket
*/

#include "shell.h"
#include "globbing.h"

static int check_brackets(const char *pattern, size_t *c_pat)
{
    if (pattern[*c_pat] != '[')
        return false;
    for (size_t i = *c_pat; pattern[i] != '\0'; i++) {
        if (pattern[i] == ']' && pattern[i - 1] != '[') {
            *c_pat = *c_pat + 1;
            return i;
        }
    }
    return false;
}

static interval_t *foobar(interval_t *interval, char *pattern, size_t *i)
{
    if (interval == NULL) {
        interval = create_interval(pattern[*i], pattern[*i + 2]);
        if (interval == NULL)
            return NULL;
    } else if (add_interval(interval, pattern[*i], pattern[*i + 2])) {
        return NULL;
    }
    *i = *i + 3;
    return interval;
}

static interval_t *get_interval_char(interval_t *interval, char *pattern)
{
    for (size_t i = 0; pattern[i] != '\0';) {
        if (pattern[i + 1] == '-' && pattern[i + 2] != '\0') {
            interval = foobar(interval, pattern, &i);
            if (interval == NULL)
                return NULL;
        } else {
            if (interval == NULL)
                interval = create_interval(pattern[i], pattern[i]);
            else if (add_interval(interval, pattern[i], pattern[i]))
                return NULL;
            if (interval == NULL)
                return NULL;
            i++;
        }
    }
    free(pattern);
    return interval;
}

int process_bracket(const char *pattern, const char *filename,
size_t *c_pat, size_t *c_fil)
{
    bool ret = false;
    interval_t *interval = NULL;
    char *bracket_content = NULL;
    int i = check_brackets(pattern, c_pat);

    if (i == false)
        return 0;
    bracket_content = strndup(pattern+(*c_pat), i - *c_pat);
    if (bracket_content == NULL)
        return -1;
    interval = get_interval_char(interval, bracket_content);
    *c_pat += i - *c_pat + 1;
    ret = check_interval(interval, filename, c_fil);
    *c_fil = *c_fil + 1;
    if (ret == 1 && filename[*c_fil] == '\0')
        return 1;
    destroy_interval(interval);
    if (ret == 0)
        return -1;
    return 0;
}