/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** 42sh
*/

#ifndef HIST_BUILT_H
#define HIST_BUILT_H

#define BADLY_FORMED "history: Badly formed number."
#define USAGE_HISTORY "Usage: history [-chrSLMT] [# number of events]."
#define FEW_ARG "history: Too many arguments."

typedef struct hist_build_s
{
    bool flag[3];
    ssize_t input;
} hist_build_t;

enum flag {
    FLAG_C = 0,
    FLAG_R,
    FLAG_H
};

#endif