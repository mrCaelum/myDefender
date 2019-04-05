/*
** EPITECH PROJECT, 2018
** options.h
** File description:
**
*/
#ifndef MY_DEFENDER_OPTIONS_H
    #define MY_DEFENDER_OPTIONS_H

    #include "scene.h"

    typedef struct game_s game_t;
    typedef enum scene scene_t;

    typedef struct options_s {
        sfMusic *music[3];
        sfFont *font;
        sfText *text[11];
        sfVector2f back_pos;
        unsigned char selected[4];
    } options_t;

    typedef struct sizes_s {
        sfVector2u size;
        char const *text;
    } sizes_t;

    typedef struct nb_select_s {
        unsigned int nb;
        char const *text;
    } nb_select_t;

    options_t *init_options(sfTexture **, sfVector2u, char const *);

    void options_events(sfRenderWindow **, sfEvent, scene_t *, game_t **);

#endif //MY_DEFENDER_OPTIONS_H
