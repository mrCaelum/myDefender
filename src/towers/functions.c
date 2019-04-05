/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Tower functions
*/

#include <math.h>
#include "towers.h"
#include "sprite_tools.h"

static void move_tower_angle(tower_t *tower)
{
    sfVector2f enemy_pos = get_middle_pos(tower->target->sprite);
    sfVector2f pos = get_middle_pos(tower->sprite[0]);
    double angle = atanf((enemy_pos.y - pos.y) / (enemy_pos.x - pos.x)) * 50;

    angle += enemy_pos.x < pos.x ? -90.0 : 90.0;
    sfSprite_setRotation(tower->sprite[1], angle);
}

static void slow(map_t *map, tower_t *tower)
{
    sfVector2f pos_en;

    for (enemy_t *tmp = map->enemies; tmp; tmp = tmp->next) {
        if (!tmp->alive)
            continue;
        pos_en = sfSprite_getPosition(tmp->sprite);
        tmp->slow = tower->is_inrange(tower, pos_en);
    }
}

static void dps(map_t *map, tower_t *tower)
{
    static int i = 0;
    sfVector2f pos_en;

    i++;
    if (i < 4)
        return;
    i = 0;
    for (enemy_t *tmp = map->enemies; tmp; tmp = tmp->next) {
        if (!tmp->alive)
            continue;
        pos_en = sfSprite_getPosition(tmp->sprite);
        if (tower->is_inrange(tower, pos_en))
            tmp->hp -= tower->strength;
    }
}

void update_towers(map_t *map)
{
    tower_t *tower;

    for (unsigned int y = 0, x = 0; y < map->size.y; x++) {
        if (x >= map->size.x) {
            x = -1;
            y++;
            continue;
        }
        if (!map->tab[y][x] || !map->tab[y][x]->tower)
            continue;
        tower = map->tab[y][x]->tower;
        if (map->enemies && tower->type != 1) {
            tower->target = set_target(map, tower);
            tower->target ? new_projectile(tower, map) : 0;
        }
        if (tower->type == 1 || tower->type == 3) {
            dps(map, tower);
        } else if (tower->type == 2) {
            slow(map, tower);
        } else if (tower->target && tower->target->sprite)
            move_tower_angle(tower);
    }
}

void draw_tower(sfRenderWindow *window, tower_t *tower)
{
    if (tower) {
        sfRenderWindow_drawSprite(window, tower->sprite[0], NULL);
        sfRenderWindow_drawSprite(window, tower->sprite[1], NULL);
        if (tower->target)
            sfRenderWindow_drawSprite(window, tower->proj->sprite, NULL);
    }
}

static void tower_attack(tower_t *tower)
 {
     sfVector2f pos_en = sfSprite_getPosition(tower->target->sprite);

     if (tower->is_inrange(tower, pos_en)) {
         tower->target->hp -= tower->strength * tower->target->strength;
     }
}

void init_tower_functions(tower_t *tower)
{
    init_tower_functions2(tower);
    tower->attack = &tower_attack;
}
