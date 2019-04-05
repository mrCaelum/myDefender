/*
** EPITECH PROJECT, 2018
** pause.c
** File description:
**
*/
#include <SFML/Graphics.h>
#include <malloc.h>
#include <textures.h>
#include "scene.h"
#include "menu.h"

static void events(sfRenderWindow *window, sfEvent event, scene_t *scene,
    menu_t *pause)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);

    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        *scene = GAME;
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    menu_events(event, scene, pause, mouse);
    if (*scene >= NO_SCENE)
        sfRenderWindow_close(window);
}

static void draw(sfRenderWindow *window, menu_t *pause)
{
    sfRenderWindow_clear(window, sfBlack);
    for (unsigned int i = 0; pause->text[i]; i++)
        sfRenderWindow_drawText(window, pause->text[i], NULL);
    sfRenderWindow_display(window);
}

void scene_pause(sfRenderWindow *window, float elapsed, scene_t *scene,
    game_t *game)
{
    sfEvent event;

    if (sfMusic_getStatus(game->pause->music[1]) != sfPlaying)
        sfMusic_play(game->pause->music[1]);
    while (sfRenderWindow_pollEvent(window, &event))
        events(window, event, scene, game->pause);
    draw(window, game->pause);
    if (*scene != PAUSE)
        sfMusic_pause(game->pause->music[1]);
    if (*scene != MENU || *scene != PLAY_MENU || *scene != PAUSE || *scene != TUTORIAL)
        sfRenderWindow_setMouseCursorVisible(window, 1);
}
