/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** __DESCRIPTION__
*/

#ifndef DEFENDER_PROJECTILE_H
    #define DEFENDER_PROJECTILE_H

    #include <SFML/Graphics.h>
    #include "map.h"

    typedef struct tower_s tower_t;

    typedef struct projectile_s {
        sfSprite *sprite;
        sfVector2f move;
    } projectile_t;

    _Bool new_projectile(tower_t *se, map_t *map);
    void move_projectiles(tower_t *tower, float elapsed);
#endif //DEFENDER_PROJECTILE_H
