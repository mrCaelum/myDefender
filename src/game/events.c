/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Game events
*/

#include "scene.h"
#include "map.h"
#include "game.h"
#include "textures.h"

static void element_event(sfEvent event, map_t *map, sfVector2i mouse,
    sfVector2u pos)
{
    sfFloatRect bounds;

    if (pos.y >= map->size.y || !map->tab[pos.y][pos.x]
    || !map->tab[pos.y][pos.x]->sprite || map->tab[pos.y][pos.x]->id != FIELD)
        return;
    bounds = sfSprite_getGlobalBounds(map->tab[pos.y][pos.x]->sprite);
    if (sfFloatRect_contains(&bounds, mouse.x, mouse.y)) {
        if (event.type == 9 && event.mouseButton.button == sfMouseLeft) {
            map->selected = map->tab[pos.y][pos.x];
            map->selected_pos = pos;
        } else
            sfSprite_setTextureRect(map->tab[pos.y][pos.x]->sprite,
                (sfIntRect){256, 0, 256, 256});
    } else
        sfSprite_setTextureRect(map->tab[pos.y][pos.x]->sprite,
            (sfIntRect){0, 0, 256, 256});
}

void game_events(sfRenderWindow *window, sfEvent event, game_t *game,
    unsigned int *scene)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);

    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        *scene = PAUSE;
    if (event.type == 9) {
        if (game->map->selected && !game->map->selected->tower
        && event.mouseButton.button == sfMouseLeft)
            buy_tower(game, mouse);
        game->map->selected = NULL;
    }
    for (unsigned int y = 0; y < game->map->size.y; y++)
        for (unsigned int x = 0; x < game->map->size.x; x++)
            element_event(event, game->map, mouse, (sfVector2u){x, y});
    if (game->map->selected)
        sfSprite_setTextureRect(game->map->selected->sprite,
            (sfIntRect){512, 0, 256, 256});
}
