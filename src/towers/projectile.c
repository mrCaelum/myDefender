/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Menu
*/

#include <projectile.h>
#include <stdlib.h>
#include <map.h>
#include <textures.h>

static _Bool set_proj(tower_t **s, map_t *m)
{
    projectile_t *tmp = (*s)->proj;

    tmp->sprite = sfSprite_create();
    if (!tmp->sprite)
        return (1);
    sfSprite_setTexture(tmp->sprite, m->texture[TEX_PROJ + (*s)->type], 1);
    sfSprite_setPosition(tmp->sprite, sfSprite_getPosition((*s)->sprite[1]));
    sfSprite_setScale(tmp->sprite, m->scaling_factor);
    tmp->move = (sfVector2f) {0, 0};
    return 0;
}

_Bool new_projectile(tower_t *se, map_t *map)
{
    if (!se->proj) {
        se->proj = malloc(sizeof(projectile_t));
        if (!se->proj)
            return (1);
    }
    return (set_proj(&se, map));
}

static sfVector2f set_move(tower_t *tower)
{
    sfVector2f pos_proj;
    sfVector2f pos_e;

    if (!tower->proj || !tower->target)
        return (sfVector2f) {};
    pos_proj = sfSprite_getPosition(tower->proj->sprite);
    pos_e = sfSprite_getPosition(tower->target->sprite);
    return (sfVector2f){(pos_e.x - pos_proj.x) / 2, (pos_e.y - pos_proj.y) / 2};
}

void move_projectiles(tower_t *tower, float elapsed)
{
    static float time = 0;

    time += elapsed;
    if (!tower->proj || !tower->proj->sprite)
        return;
    tower->proj->move = set_move(tower);
    sfSprite_move(tower->proj->sprite, tower->proj->move);
    if (tower->target) {
        if (time >= 1) {
             tower->attack(tower);
             time -= 1;
         }
    }
}
