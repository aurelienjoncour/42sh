/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#include <unistd.h>
#include <term.h>
#include <termios.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h>
#include "my_key.h"

bool init_input(void)
{
    int ret;
    int i;
    char *s;

    if (isatty(0) == 1) {
        i = setupterm("xterm", 1, &ret);
        if (i == -1)
            return false;
        s = tigetstr("smkx");
        if (s)
            write(2, s, strlen(s));
    }
    return true;
}

static void canonical_mode_select(bool enable)
{
    static struct termios old;
    static struct termios new;

    if (enable) {
        ioctl(0, TCGETS, &old);
        ioctl(0, TCGETS, &new);

        new.c_lflag &= ~ECHO;
        new.c_lflag &= ~ICANON;
        ioctl(0, TCSETS, &new);
    }
    else if (!enable) {
        ioctl(0, TCSETS, &old);
    }
}

static int special_key(char *in)
{
    if (in[0] == 27 && in[1] == 91 && in[2] == 51)
        return SUPPR_DC;
    if (!(in[0] == 27 && in[1] == 'O'))
        return 0;
    if (in[2] == 'D')
        return LEFT;
    if (in[2] == 'C')
        return RIGHT;
    if (in[2] == 'B')
        return DOWN;
    if (in[2] == 'A')
        return UP;
    if (in[2] == 'H')
        return GO_START;
    if (in[2] == 'F')
        return GO_END;
    return 0;
}

int my_getch(void)
{
    int ret;
    char buf[4] = {0};

    canonical_mode_select(true);
    ret = read(0, buf, 4);
    if (ret <= 0)
        return 0;
    canonical_mode_select(false);
    if (buf[1] == '\0')
        return (int) buf[0];
    return special_key(buf);
}