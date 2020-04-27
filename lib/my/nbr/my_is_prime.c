/*
** EPITECH PROJECT, 2019
** CPool_Day05_2019
** File description:
** Task06
*/

#include "my.h"

static size_t my_square_about(const size_t nb)
{
    size_t result = 1;

    while ((result * result) < nb && result <= 46340)
        result++;
    return (result);
}

bool my_is_prime(const size_t nb)
{
    size_t sqrt_nb = my_square_about(nb);

    if (nb < 2)
        return false;
    for (size_t div = 2; div <= sqrt_nb; div++) {
        if (nb % div == 0 && nb != div) {
            return false;
        }
    }
    return true;
}
