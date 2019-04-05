/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Map header file
*/

#ifndef MAP_H_
    #define MAP_H_

    #include "towers.h"
    #include "game.h"

    typedef struct tower_s tower_t;
    typedef struct enemy_s enemy_t;
    typedef struct projectile_s projectile_t;
    typedef struct game_menu_s game_menu_t;

    typedef enum {FIELD, ROAD, PORTAL, CASTLE} element_id_t;

    typedef struct map_element_s {
        element_id_t id;
        sfSprite *sprite;
        tower_t *tower;
    } map_element_t;

    typedef struct map_s {
        sfVector2u size;
        sfVector2f scaling_factor;
        sfVector2f center_factor;
        enemy_t *enemies;
        sfTexture **texture;
        map_element_t ***tab;
        map_element_t *selected;
        game_menu_t *game_menu;
        sfVector2u selected_pos;
        unsigned int hp;
        sfRectangleShape *life_preview;
    } map_t;

    struct map_create_tab_s {
        char character;

        map_element_t *(*create)(map_t *, sfTexture **, sfVector2u);
    };

    map_t *map_create_from_file(char const *, sfTexture **, sfVector2u);

    map_element_t *create_field(map_t *, sfTexture **, sfVector2u);

    map_element_t *create_road(map_t *, sfTexture **, sfVector2u);

    map_element_t *create_portal(map_t *, sfTexture **, sfVector2u);

    map_element_t *create_castle(map_t *, sfTexture **, sfVector2u);

    map_element_t *get_map_element(map_t *, element_id_t);

#endif
