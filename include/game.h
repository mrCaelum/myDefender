/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Game header file
*/

#ifndef GAME_H_
    #define GAME_H_

    #include <SFML/Graphics/Types.h>
#include <SFML/Audio/Types.h>
#include "scene.h"

    #ifndef TOTAL_TOWERS
        #define TOTAL_TOWERS 4
    #endif
    #ifndef LOWER
        #define LOWER(x, y) (x < y ? x : y)
    #endif
    #ifndef MAX_MAP_SIZE
        #define MAX_MAP_SIZE 2048
    #endif

    typedef struct map_s map_t;
    typedef struct game_s game_t;

    typedef enum direction {RIGHT, LEFT, TOP, BOTTOM} direction_t;

    typedef struct money_preview_s {
        sfSprite *coin;
        sfFont *font;
        sfText *money;
    } money_preview_t;

    typedef struct game_menu_s {
        sfRenderWindow *window;
        sfTexture **texture;
        money_preview_t money_preview;
        sfSprite *background;
        sfSprite **towers;
        unsigned int money;
        sfMusic *music;
    } game_menu_t;

    sfRenderWindow *create_window(sfVector2u, _Bool);

    game_t *init_game(sfRenderWindow *, sfTexture **, char const *, char const *);

    void destroy_game(game_t *);

    game_menu_t *init_game_menu(sfTexture **, sfRenderWindow *, sfMusic *);

    void anim_game_menu(game_menu_t *, int);

    void buy_tower(struct game_s *, sfVector2i);

    void init_money_preview(sfTexture **, game_menu_t *);

    void update_money_preview(game_menu_t *);

    void draw_money_preview(sfRenderWindow *, game_menu_t *);

    void game_events(sfRenderWindow *, sfEvent, game_t *, unsigned int *);

#endif
