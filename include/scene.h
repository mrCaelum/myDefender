/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Scene header file
*/

#ifndef SCENE_H_
    #define SCENE_H_

    #include "map.h"
    #include "menu.h"
    #include "game.h"
    #include "inventory.h"
    #include "options.h"

    typedef struct menu_s menu_t;

    typedef enum scene {
        MENU, PLAY_MENU, OPTIONS, GAME, PAUSE, TUTORIAL, NO_SCENE
    } scene_t;

    typedef struct game_s {
        struct map_s *map;
        struct game_menu_s *game_menu;
        menu_t *menu;
        menu_t *play_menu;
        menu_t *pause;
        options_t *options;
        menu_t *tutorial;
    } game_t;

    struct scene_call_s {
        scene_t id;

        void (*scene)(sfRenderWindow *, float, scene_t *, game_t *);
    };

    void call_scene(sfRenderWindow *, float, scene_t *, game_t *);

    void scene_menu(sfRenderWindow *, float, scene_t *, game_t *);

    void scene_play_menu(sfRenderWindow *, float, scene_t *, game_t *);

    void scene_options(sfRenderWindow **, float, scene_t *, game_t **);

    void scene_game(sfRenderWindow *, float, scene_t *, game_t *);

    void scene_pause(sfRenderWindow *, float, scene_t *, game_t *);

    void scene_tutorial(sfRenderWindow *, float, scene_t *, game_t *);

#endif
