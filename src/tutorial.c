/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Tutorial
*/

#include <textures.h>
#include "scene.h"
#include "game.h"
#include "menu.h"

static void
events(sfRenderWindow *window, sfEvent event, scene_t *scene, menu_t *menu)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);

    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        *scene = PLAY_MENU;
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
//    menu_events(event, scene, menu, mouse);
    if (*scene >= NO_SCENE)
        sfRenderWindow_close(window);
}

static void draw(sfRenderWindow *window, menu_t *menu)
{
    sfRenderWindow_clear(window, sfBlack);
    for (unsigned int i = 0; menu->text[i]; i++)
        sfRenderWindow_drawText(window, menu->text[i], NULL);
    sfRenderWindow_display(window);
}

void scene_tutorial(sfRenderWindow *window, float elapsed, scene_t *scene,
                game_t *game)
{
    sfEvent event;

    if (sfMusic_getStatus(game->tutorial->music[1]) != sfPlaying)
        sfMusic_play(game->tutorial->music[1]);
    while (sfRenderWindow_pollEvent(window, &event))
        events(window, event, scene, game->tutorial);
    draw(window, game->tutorial);
    if (*scene != TUTORIAL)
        sfMusic_pause(game->tutorial->music[1]);
    if (*scene != MENU || *scene != PLAY_MENU || *scene != PAUSE || *scene != TUTORIAL)
        sfRenderWindow_setMouseCursorVisible(window, 1);
}
