/*
** EPITECH PROJECT, 2018
** enemy.h
** File description:
**
*/
#ifndef MY_DEFENDER_ENEMY_H
    #define MY_DEFENDER_ENEMY_H

    #include <SFML/Graphics.h>
    #include "map.h"

    typedef struct map_s map_t;

    typedef struct enemy_s {
        unsigned char type;
        sfSprite *sprite;
        int hp;
        unsigned int init_hp;
        sfRectangleShape *hp_bar;
        unsigned int strength;
        unsigned int id;
        sfVector2f move_vector;
        _Bool slow;
        _Bool alive;
        struct enemy_s *next;
        struct enemy_s *prev;
    } enemy_t;

    int init_enemy(unsigned char, map_t *);

    void move_enemy(map_t *);

    void destroy_enemy(enemy_t *, map_t *);

    void draw_enemies(sfRenderWindow *window, map_t *map);

#endif //MY_DEFENDER_ENEMY_H
