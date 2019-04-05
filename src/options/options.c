/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Options
*/

#include <SFML/Graphics/Types.h>
#include <scene.h>
#include <malloc.h>
#include <textures.h>
#include "game.h"
#include "options.h"

static void draw(sfRenderWindow *window, options_t *options)
{
    sfRenderWindow_clear(window, sfBlack);
    for (unsigned int i = 0; options->text[i]; i++)
        sfRenderWindow_drawText(window, options->text[i], NULL);
    sfRenderWindow_display(window);
}

void scene_options(sfRenderWindow **window, float elapsed, scene_t *scene,
    game_t **game)
{
    sfEvent event;

    if (sfMusic_getStatus((*game)->options->music[1]) != sfPlaying)
        sfMusic_play((*game)->options->music[1]);
    while (sfRenderWindow_pollEvent((*window), &event))
        options_events(window, event, scene, game);
    draw((*window), (*game)->options);
    if (*scene != OPTIONS)
        sfMusic_pause((*game)->menu->music[1]);
}
