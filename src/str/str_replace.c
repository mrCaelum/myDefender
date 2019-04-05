/*
** EPITECH PROJECT, 2019
** lib_str
** File description:
** Str replace function
*/

#include "str.h"

static char *paste_str(char *str, char const *str1, char const *str2, int size)
{
    char *new = malloc((size + 1) * sizeof(char));

    if (!new)
        return (NULL);
    for (int i = 0, j = 0; str[j]; i++, j++) {
        if (str_startwith(&str[j], str1)) {
            str_copy(&new[i], str2);
            j += str_length(str1) - 1;
            i += str_length(str2) - 1;
        } else
            new[i] = str[j];
    }
    new[size] = 0;
    free(str);
    return (new);
}

char *str_replace(char *str, char const *str1, char const *str2)
{
    int size = 0;

    if (str_is_equal(str, str1)) {
        free(str);
        return (str_alloc(str2));
    }
    for (int i = 0; str[i]; size++, i++)
        if (str_startwith(&str[i], str1)) {
            i += str_length(str1);
            size += str_length(str2);
        }
    return (paste_str(str, str1, str2, size));
}
