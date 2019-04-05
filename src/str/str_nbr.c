/*
** EPITECH PROJECT, 2019
** lib_str
** File description:
** str_nbr functions
*/

#include "str.h"

char *int_to_str(int nb)
{
    char *str;
    int size = 1;

    for (int i = nb; i > 9; i /= 10, size++);
    str = malloc((size + 1) * sizeof(char));
    str[size--] = 0;
    for (int i = size; i >= 0; i--) {
        str[i] = nb % 10 + '0';
        nb /= 10;
    }
    return (str);
}
