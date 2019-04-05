/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Scene loader
*/

#include <scene.h>
#include "game.h"

static const struct scene_call_s scenes_tab[] = {
    {MENU, &scene_menu},
    {PLAY_MENU, &scene_play_menu},
    {GAME, &scene_game},
    {PAUSE, &scene_pause},
    {TUTORIAL, &scene_tutorial},
    {0, NULL}
};

void call_scene(sfRenderWindow *window, float elapsed, scene_t *scene,
    game_t *game)
{
    for (int i = 0; scenes_tab[i].scene; i++)
        if (scenes_tab[i].id == (*scene))
            scenes_tab[i].scene(window, elapsed, scene, game);
}
