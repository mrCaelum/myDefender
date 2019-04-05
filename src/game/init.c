/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Main file
*/

#include <textures.h>
#include <map.h>
#include <menu.h>
#include <scene.h>
#include <options.h>
#include <zconf.h>
#include <fcntl.h>
#include "game.h"

static const char *menu_str_tab[] = {
    "my defender",
    "play",
    "options",
    "quit",
    NULL
};

static const char *play_str_tab[] = {
    "my defender",
    "new game",
    "continue",
    "tutorial",
    "back",
    NULL
};

static const char *pause_str_tab[] = {
    "pause",
    "resume",
    "main menu",
    "exit game",
    NULL
};

static const char *tutorial_str_tab[] = {
        "Tutorial",
        "Click on a grass tile to select the position of the tower",
        "Open menu by sliding the mouse on the bottom of the screen",
        "or by pressing I",
        "Click on the tower to buy and place it on the tile youve chosen",
        "Press Escape to go back",
        NULL
};

static const scene_t menu_tab[] = {
    PLAY_MENU,
    OPTIONS,
    NO_SCENE
};

static const scene_t play_tab[] = {
    GAME,
    PLAY_MENU,
    TUTORIAL,
    MENU
};

static const scene_t pause_tab[] = {
    GAME,
    MENU,
    NO_SCENE
};

static const scene_t tutorial_tab[] = {
        MENU,
        NO_SCENE
};

static void set_inactive_menu_element(game_t *game)
{
    game->play_menu->active[2] = 0;
    for (int i = 0; game->tutorial->active[i]; i++)
        game->tutorial->active[i] = 0;
}

game_t *init_game(sfRenderWindow *window, sfTexture **texture,
    char const *file, char const *size)
{
    game_t *game = malloc(sizeof(game_t));
    sfVector2u window_size = sfRenderWindow_getSize(window);

    if (!game)
        return (NULL);
    game->map = map_create_from_file(file ? file : "resources/test.map", texture,
        window_size);
    game->options = init_options(texture, window_size, size);
    game->game_menu = init_game_menu(texture, window, game->options->music[2]);
    if (!game->map || !game->game_menu || !game->options)
        return (NULL);
    game->map->game_menu = game->game_menu;
    game->menu = init_menu(window, menu_str_tab, menu_tab,
        game->options->music[1]);
    game->play_menu = init_menu(window, play_str_tab, play_tab,
        game->options->music[1]);
    game->pause = init_menu(window, pause_str_tab, pause_tab,
        game->options->music[1]);
    game->tutorial = init_menu(window, tutorial_str_tab, tutorial_tab,
        game->options->music[1]);
    if (!game->menu || !game->play_menu || !game->pause)
        return (NULL);
    return (set_inactive_menu_element(game), game);
}

void destroy_game(game_t *game)
{
    sfMusic_destroy(game->options->music[0]);
    sfMusic_destroy(game->options->music[1]);
    sfMusic_destroy(game->options->music[2]);
    destroy_menu(game->menu);
    destroy_menu(game->play_menu);
    destroy_menu(game->pause);
    destroy_menu(game->tutorial);
    free(game);
}
