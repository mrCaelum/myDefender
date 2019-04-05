/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Play menu
*/

#include <SFML/Graphics.h>
#include <malloc.h>
#include <textures.h>
#include "scene.h"
#include "menu.h"

static void events(sfRenderWindow *window, sfEvent event, scene_t *scene,
    menu_t *play_menu)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);

    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        *scene = MENU;
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    menu_events(event, scene, play_menu, mouse);
    if (*scene >= NO_SCENE)
        sfRenderWindow_close(window);
}

static void draw(sfRenderWindow *window, menu_t *play_menu)
{
    sfRenderWindow_clear(window, sfBlack);
    for (unsigned int i = 0; play_menu->text[i]; i++)
        sfRenderWindow_drawText(window, play_menu->text[i], NULL);
    sfRenderWindow_display(window);
}

void scene_play_menu(sfRenderWindow *window, float elapsed, scene_t *scene,
    game_t *game)
{
    sfEvent event;

    if (sfMusic_getStatus(game->play_menu->music[1]) != sfPlaying)
        sfMusic_play(game->play_menu->music[1]);
    while (sfRenderWindow_pollEvent(window, &event))
        events(window, event, scene, game->play_menu);
    draw(window, game->play_menu);
    if (*scene != PLAY_MENU)
        sfMusic_pause(game->play_menu->music[1]);
    if (*scene != MENU || *scene != PLAY_MENU || *scene != PAUSE || *scene != TUTORIAL)
        sfRenderWindow_setMouseCursorVisible(window, 1);
}
