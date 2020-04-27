/*
** EPITECH PROJECT, 2019
** CPool_Day04_2019
** File description:
** Task01
*/

#include "my.h"

void my_swap(int *a, int *b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
}
