/*
** EPITECH PROJECT, 2018
** towers.c
** File description:
**
*/

#include <SFML/Graphics.h>
#include "towers.h"
#include <math.h>
#include <malloc.h>
#include <projectile.h>
#include "textures.h"
#include "map.h"

static void tower_draw_stats(sfRenderWindow *window, tower_t *tower)
{
    sfRenderWindow_drawText(window, tower->tower_stats.title, NULL);
    for (unsigned int i = 0; i < 2; i++)
        sfRenderWindow_drawText(window, tower->tower_stats.stat[i], NULL);
}

static _Bool tower_inrange(tower_t *self, sfVector2f pos)
{
    sfVector2f self_pos = sfSprite_getPosition(self->sprite[0]);
    double distance =
    sqrt(pow(self_pos.x - pos.x, 2) + pow(self_pos.y - pos.y, 2));

    return (distance <= self->range);
}

enemy_t *set_target(map_t *map, tower_t *tower)
{
    enemy_t *tmp = map->enemies;

    for(; tmp->next; tmp = tmp->next)
        if(tmp->alive && tower->is_inrange(tower, sfSprite_getPosition(tmp->sprite)))
            return (tmp);
    return (NULL);
}

void init_tower_functions2(tower_t *tower)
{
    tower->draw_stats = &tower_draw_stats;
    tower->is_inrange = &tower_inrange;
}
