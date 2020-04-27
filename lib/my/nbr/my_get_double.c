/*
** EPITECH PROJECT, 2019
** 102architech_2019
** File description:
** extract the number in a parameter (check error)
*/

#include "my.h"

static bool is_digit(char c, int len_nbr)
{
    if ((c > '0' && c <= '9') || (c == '0' && len_nbr > 0))
        return true;
    return false;
}

static int incr_len(unsigned int *len, char c, char after_dot)
{
    if (is_digit(c, len[0])) {
        len[0]++;
    } else if (c != '.' && c != '0' && c != '-') {
        my_putstr_error("my_get_double error : arg\n");
        return EXIT_ERROR;
    }
    if (is_digit(c, len[1]) && after_dot == 0)
        len[1]++;
    else if (is_digit(c, 1) && after_dot == 1)
        len[2]++;
    return EXIT_SUCCESS;
}

static unsigned int *len_nbr(const char *nbr)
{
    unsigned int *len = malloc(sizeof(unsigned int) * 3);
    int i = -1;
    char after_dot = 0;
    int zero_counter = 0;

    if (!len)
        return NULL;
    for (size_t i = 0; i < 3; i++)
        len[i] = 0;
    while (nbr[++i] != '\0') {
        if (nbr[i] == '.')
            after_dot = 1;
        if (nbr[i] == '0')
            zero_counter++;
        if (incr_len(len, nbr[i], after_dot) == EXIT_ERROR)
            return NULL;
    }
    if (len[0] == 0 && zero_counter > 0)
        len[0] = 1;
    return len;
}

static ssize_t get_dot_idx(const char *nbr)
{
    for (ssize_t i = 0; nbr[i] != '\0'; i++) {
        if (nbr[i] == '.')
            return i;
    }
    return -1;
}

double my_get_double(const char *nbr)
{
    unsigned int *len = len_nbr(nbr);
    ssize_t dot_idx = get_dot_idx(nbr);
    double alpha = 0;
    double beta = 0;

    if (!len || len[0] == 0 || len[0] > 39) {
        my_putstr_error("my_get_double : error\n");
        return 0;
    }
    if (dot_idx == -1 || len[2] == 0) {
        free(len);
        return ((double)my_getnbr(nbr));
    }
    if (len[1] != 0)
        alpha = my_getnbr(nbr);
    beta = (double)my_getnbr(&nbr[dot_idx]) / my_compute_power_rec(10, len[2]);
    if (alpha < 0 || (nbr[0] == '-' && alpha == 0))
        beta = -beta;
    free(len);
    return (alpha + beta);
}
