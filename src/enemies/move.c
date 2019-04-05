/*
** EPITECH PROJECT, 2018
** enemy.c
** File description:
** Enemies
*/

#include <malloc.h>
#include <map.h>
#include <time.h>
#include "game.h"
#include "enemy.h"
#include "textures.h"
#include <stdlib.h>
#include <zconf.h>
#include <fcntl.h>

static sfVector2i get_next_map(map_t *map, int y, int x, sfVector2i mv)
{
    sfVector2i xy = (sfVector2i){0, 0};

    if (map->tab[y + mv.y][x + mv.x]
    && map->tab[y + mv.y][x + mv.x]->id != FIELD)
        return (mv);
    else if (!mv.x) {
        if (map->tab[y][x + 1] && map->tab[y][x + 1]->id != FIELD)
            return (xy.x = 1, xy);
        else if (map->tab[y][x - 1] && map->tab[y][x - 1]->id != FIELD)
            return (xy.x = -1, xy);
    } else {
        if (map->tab[y + 1][x] && map->tab[y + 1][x]->id != FIELD)
            return (xy.y = 1, xy);
        else if (map->tab[y - 1][x] && map->tab[y - 1][x]->id != FIELD)
            return (xy.y = -1, xy);
    }
    return xy;
}

static void move(map_t *map, int y, int x)
{
    sfFloatRect rect = sfSprite_getGlobalBounds(map->tab[y][x]->sprite);
    sfFloatRect mob_rect;
    sfVector2f pos;
    sfVector2i next = (sfVector2i){0, 0};
    enemy_t *tmp = map->enemies;

    rect.left += rect.width / 3;
    rect.top += rect.height / 3;
    rect.width /= 3;
    rect.height /= 3;
    if (!tmp)
        return;
    for (unsigned int id = 0; tmp; tmp = tmp->next, id++) {
        if (!tmp->alive)
            continue;
        mob_rect = sfSprite_getGlobalBounds(tmp->sprite);
        pos.x = mob_rect.left + mob_rect.width / 2;
        pos.y = mob_rect.top + mob_rect.height / 2;
        if ((sfFloatRect_contains(&rect, pos.x, pos.y)
        && map->tab[y][x] && map->tab[y][x]->id == CASTLE) || (tmp->hp <= 0)) {
            map->hp -= map->tab[y][x]->id == CASTLE && tmp->hp > 0 ? tmp->strength * 2 : 0;
            map->game_menu->money += map->tab[y][x]->id != CASTLE && tmp->hp <= 0 ? 5 : 0;
            tmp->alive = 0;
            continue;
        }
        if (sfFloatRect_contains(&rect, pos.x, pos.y)) {
            next = get_next_map(map, y, x, (sfVector2i)
            {(int)tmp->move_vector.x,
                (int)tmp->move_vector.y});
            tmp->move_vector = (sfVector2f){0, 0};
            tmp->move_vector = (sfVector2f){(float)next.x, (float)next.y};
        }
    }
}

void move_enemy(map_t *map)
{
    for (unsigned int y = 0, x = 0; y < map->size.y; x++) {
        if (x >= map->size.x) {
            x = -1;
            y++;
        } else if (map->tab[y][x] && map->tab[y][x]->id != FIELD)
            move(map, y, x);
    }
}
