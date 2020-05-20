/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** get_home_path
*/

#include "shell.h"

char *get_home_path(void)
{
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (pw == NULL) {
        return NULL;
    }
    return strdup(pw->pw_dir);
}