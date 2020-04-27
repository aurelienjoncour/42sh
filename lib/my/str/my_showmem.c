/*
** EPITECH PROJECT, 2019
** CPool_Day06_2019
** File description:
** Task21
*/

#include "my.h"

static void disp_lastchar(char const *str, int index, int nb)
{
    for (size_t i = nb; i > 0; i--) {
        if (str[index - i] < 32 || str[index - i] > 126)
            my_putchar('.');
        else
            my_putchar(str[index - i]);
    }
}

static void base_conv(int nb, int base, char const *basestr, int lennb)
{
    int res[100];
    int i = 0;

    while (nb != 0) {
        res[i++] = (nb % base);
        nb /= base;
    }
    for (ssize_t j = 0; j < (lennb - i); j++)
        my_putchar('0');
    for (ssize_t j = (i - 1); j >= 0; j--)
        my_putchar(basestr[res[j]]);
}

static void disp_asciihex(int *adr, char const *str, int nb)
{
    for (size_t i = 0; i < (size_t)nb; i++) {
        base_conv(str[*adr], 16, "0123456789abcdef", 2);
        if (*adr % 2 != 0)
            my_putchar(' ');
        (*adr)++;
    }
    for (size_t i = 0; i < (size_t)(16 - nb); i++) {
        for (size_t j = 0; j < 2; j++)
            my_putchar(' ');
        if (i % 2 != 0)
            my_putchar(' ');
    }
    if (nb % 2 != 0)
        my_putchar(' ');
}

static void disp(int *adr, char const *str, int nb)
{
    base_conv(*adr, 16, "0123456789abcdef", 8);
    my_putchar(':');
    my_putchar(' ');
    disp_asciihex(adr, str, nb);
    disp_lastchar(str, *adr, nb);
    my_putchar('\n');
}

int my_showmem(char const *str, int size)
{
    int adr = 0;

    for (size_t i = 0; i < (size_t)(size / 16); i++)
        disp(&adr, str, 16);
    if (size % 16 != 0) {
        disp(&adr, str, (size % 16));
    }
    return EXIT_SUCCESS;
}
