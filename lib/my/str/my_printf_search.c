/*
** EPITECH PROJECT, 2019
** PSU_my_printf_2019
** File description:
** my_printf
*/

#include "my.h"
#include "my_printf.h"

static const char FLAGS[5] = {'#', '0', '-', ' ', '+'};
static const char *SPECIF[12] = {"d", "i", "u", "o", "x", "X", "c", "s", "S",
"p", "%", "b"};
static const char *LEN[] = {"hh", "h", "ll", "l", "q"};

void search_flags(char *format, int *i, arg_t *arg)
{
    short arg_idx = 0;

    while (arg_idx < 5) {
        if (format[*i] == FLAGS[arg_idx]) {
            arg->flags[arg_idx] = FLAGS[arg_idx];
            break;
        }
        arg_idx++;
    }
    if (arg_idx < 5) {
        (*i)++;
        search_flags(format, i, arg);
    }
}

int search_specifier(char *format, int *i, char dest[2])
{
    int pattern_found = -1;

    for (size_t idx_pat = 0; idx_pat < LSPECIF; idx_pat++) {
        if (SPECIF[idx_pat][0] == format[*i]) {
            pattern_found = idx_pat;
            break;
        }
    }
    if (pattern_found != -1) {
        my_strcpy(dest, SPECIF[pattern_found]);
        return 0;
    }
    return -1;
}

static int search_length_ext(int pattern_found, char *dest, int *i)
{
    if (pattern_found != -1) {
        *i += my_strlen(LEN[pattern_found]);
        my_strcpy(dest, LEN[pattern_found]);
        return 0;
    }
    return -1;
}

int search_length(char *format, int *i, char *dest)
{
    int pattern_found = -1;
    int idx_pat = 0;

    for (ssize_t j = 0; idx_pat < LLEN && LEN[idx_pat][j] != '\0'; j++) {
        if (LEN[idx_pat][j] != format[*i + j]) {
            idx_pat++;
            j = -1;
        }
        if (j != -1 && LEN[idx_pat][j + 1] == '\0' && pattern_found == -1)
            pattern_found = idx_pat;
        else if (j != -1 && LEN[idx_pat][j + 1] == '\0') {
            *dest = my_strlen(LEN[pattern_found]);
            return 1;
        }
    }
    return search_length_ext(pattern_found, dest, i);
}
