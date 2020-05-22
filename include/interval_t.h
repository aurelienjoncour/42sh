/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** interval_t
*/

#ifndef INTERVAL_T_H_
#define INTERVAL_T_H_

typedef struct interval_t{
    char c[2];
    struct interval_t *next;
}interval_t;


#endif /* !INTERVAL_T_H_ */
