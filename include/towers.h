/*
** EPITECH PROJECT, 2018
** towers.h
** File description:
** Tower
*/

#ifndef MY_DEFENDER_TOWERS_H
    #define MY_DEFENDER_TOWERS_H

    #include "enemy.h"
    #include "map.h"
    #include "projectile.h"

    typedef struct map_s map_t;
    typedef struct map_element_s map_element_t;
    typedef struct tower_s tower_t;
    typedef struct projectile_s projectile_t;

    typedef struct tower_stats_s {
        sfFont *font;
        sfText *title;
        sfText *stat[2];
    } tower_stats_t;

    typedef struct tower_s {
        tower_stats_t tower_stats;
        sfSprite *sprite[2];
        int strength;
        float range;
        float r_speed;
        sfCircleShape *range_preview[20];
        unsigned char type;
        enemy_t *target;
        projectile_t *proj;

        void (*draw_stats)(sfRenderWindow *, struct tower_s *);
        _Bool (*is_inrange)(struct tower_s *, sfVector2f);
        void (*attack)(tower_t *tower);
    } tower_t;

    int create_tower(unsigned char, map_t *);
    void tower_destroy(tower_t *);
    void update_towers(map_t *map);
    void draw_tower(sfRenderWindow *, tower_t *);
    enemy_t *set_target(map_t *map, tower_t *tower);
    void init_tower_functions(tower_t *);
    void init_tower_functions2(tower_t *);

#endif
