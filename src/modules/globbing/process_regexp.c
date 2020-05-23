/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** Created: 2020-05-15T08:53:41+02:00 | Author: simon
*/

#include "globbing.h"

static char *clean_patern_string(const char *patern)
{
    char *new_str = malloc(sizeof(char) * (strlen(patern) + 1));
    size_t index = 0;

    if (new_str == NULL)
        return NULL;
    memset(new_str, 0, strlen(patern) + 1);
    for (size_t i = 0; patern[i] != '\0'; i++) {
        if (!(patern[i] == '*' && patern[i + 1] == '*')) {
            new_str[index] = patern[i];
            index++;
        }
    }
    return new_str;
}

static bool analyse_end(const char *pattern, const char *filename,
size_t c_pat, size_t c_fil)
{
    if (filename[c_fil] == '\0' && pattern[c_pat] != '\0') {
        for (size_t i = c_pat; pattern[i] != '\0'; i++) {
            if (pattern[i] != '*')
                return false;
        }
    }
    if (pattern[c_pat] == '\0' && filename[c_fil] != '\0')
        return false;
    return true;
}

static int process_asterix(const char *pattern, const char *filename,
size_t *c_pat, size_t *c_fil) {
    if (pattern[*c_pat] == '?' || (pattern[*c_pat] == filename[*c_fil])) {
        *c_pat = *c_pat + 1;
        *c_fil = *c_fil + 1;
    } else if (pattern[*c_pat] == '*') {
        *c_pat = *c_pat + 1;
        if (pattern[*c_pat] == '\0')
            return 1;
        while (pattern[*c_pat] != filename[*c_fil]) {
            if (filename[*c_fil] == '\0' || pattern[*c_pat] == '\0')
                return -1;
            *c_fil = *c_fil + 1;
        }
        *c_pat = *c_pat + 1;
        *c_fil = *c_fil + 1;
    } else {
        return -1;
    }
    return 0;
}

static int analyse_regexp(char *new_pattern, const char *filename,
size_t *c_pat, size_t *c_fil)
{
    int ret = 0;

    ret = process_bracket(new_pattern, filename, c_pat, c_fil);
    if (ret == -1) {
        free(new_pattern);
        return -1;
    } else if (ret == 1) {
        free(new_pattern);
        return 1;
    }
    ret = process_asterix(new_pattern, filename, c_pat, c_fil);
    if (ret == -1) {
        free(new_pattern);
        return -1;
    } else if (ret == 1) {
        free(new_pattern);
        return 1;
    }
    return 0;
}

bool process_regexp(const char *pattern, const char *filename)
{
    int ret = true;
    char *new_pattern = clean_patern_string(pattern);
    size_t c_pat = 0;
    size_t c_fil = 0;

    if (new_pattern == NULL)
        return false;
    while (new_pattern[c_pat] != '\0' && filename[c_fil] != '\0') {
        ret = analyse_regexp(new_pattern, filename, &c_pat, &c_fil);
        if (ret == -1) {
            return false;
        } else if (ret == 1) {
            return true;
        }
    }
    ret = analyse_end(new_pattern, filename, c_pat, c_fil);
    free(new_pattern);
    return ret;
}
