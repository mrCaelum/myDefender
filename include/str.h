/*
** EPITECH PROJECT, 2019
** lib_str
** File description:
** String library
*/

#ifndef STR_H_
    #define STR_H_

    #include <unistd.h>
    #include <stdlib.h>

    int str_length(char const *);

    char *str_alloc(char const *);

    void str_copy(char *, char const *);

    char *str_concat(char const *, char const *);

    char *str_reverse(char *);

    void str_replace_char(char *, char, char);

    char *str_replace(char *, char const *, char const *);

    char *str_remove_char(char *, char);

    char *sub_str(char const *, char);

    char *str_upcase(char *);

    char **str_to_tab(char *, char);

    char *tab_to_str(char **, char);

    int str_contains(char const *, char);

    int str_is_equal(char const *, char const *);

    int str_compare(char const *, char const *, int);

    int str_startwith(char const *, char const *);

    int str_endwith(char const *, char const *);

    char *int_to_str(int);

#endif
