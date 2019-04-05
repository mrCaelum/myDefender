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

static int ENEMY_HP[3] = {100, 150, 200};
static int ENEMY_STRENGTH[3] = {10, 12, 15};

void draw_enemies(sfRenderWindow *window, map_t *map)
{
    enemy_t *tmp = map->enemies;
    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);
    sfFloatRect rect;
    sfVector2f move;

    if (!tmp)
        return;
    for (unsigned int id = 0; tmp; tmp = tmp->next, id++) {
        if (!tmp->alive)
            continue;
        move = (sfVector2f){tmp->move_vector.x * (float)(tmp->slow ? 0.7 : 1),
            tmp->move_vector.y * (float)(tmp->slow ? 0.7 : 1)};
        sfRectangleShape_setSize(tmp->hp_bar, (sfVector2f)
        {(float)tmp->hp / (float)tmp->init_hp * 128 * map->scaling_factor.x,
            16 * map->scaling_factor.y});
        sfRectangleShape_move(tmp->hp_bar, move);
        sfSprite_move(tmp->sprite, move);
        rect = sfSprite_getGlobalBounds(tmp->sprite);
        if (sfFloatRect_contains(&rect, mouse.x, mouse.y))
            sfRenderWindow_drawRectangleShape(window, tmp->hp_bar, NULL);
        sfRenderWindow_drawSprite(window, tmp->sprite, NULL);
    }
}

static void setup_hp_bar(map_t *map, enemy_t *enemy, unsigned char type,
    sfFloatRect spawn_bounds)
{
    sfFloatRect enemy_bounds = sfSprite_getGlobalBounds(enemy->sprite);

    enemy->init_hp = ENEMY_HP[type] + enemy->id * 2;
    enemy->hp = ENEMY_HP[type] + enemy->id * 2;
    sfRectangleShape_setFillColor(enemy->hp_bar, sfRed);
    sfRectangleShape_setSize(enemy->hp_bar, (sfVector2f)
    {256 * map->scaling_factor.x, 16 * map->scaling_factor.x});
    sfRectangleShape_setPosition(enemy->hp_bar, (sfVector2f)
    {spawn_bounds.left + spawn_bounds.width / 2 - 64 * map->scaling_factor.x,
    enemy_bounds.top - 20 * map->scaling_factor.y});
}

static _Bool setup_enemies(map_t *map, unsigned char type, enemy_t *enemy)
{
    map_element_t *spawn = get_map_element(map, PORTAL);
    sfFloatRect spawn_bounds = sfSprite_getGlobalBounds(spawn->sprite);

    enemy->sprite = sfSprite_create();
    enemy->hp_bar = sfRectangleShape_create();
    if (!enemy->sprite || !enemy->hp_bar)
        return (1);
    sfSprite_setTexture(enemy->sprite,
        map->texture[TEX_ENEMY + type], 1);
    sfSprite_setTextureRect(enemy->sprite, (sfIntRect) {0, 0, 11, 12});
    sfSprite_setScale(enemy->sprite, (sfVector2f)
    {8 * map->scaling_factor.x, 8 * map->scaling_factor.y});
    sfSprite_setPosition(enemy->sprite, (sfVector2f){spawn_bounds.left +
        spawn_bounds.width / 3, spawn_bounds.top + spawn_bounds.height / 3});
    setup_hp_bar(map, enemy, type, spawn_bounds);
    enemy->type = type;
    enemy->strength = ENEMY_STRENGTH[type];
    enemy->move_vector = (sfVector2f) {1, 0};
    enemy->slow = 0;
    enemy->alive = 1;
    return (0);
}

int init_enemy(unsigned char type, map_t *map)
{
    enemy_t *tmp = map->enemies;

    if (!map->enemies) {
        map->enemies = malloc(sizeof(enemy_t));
        if (!map->enemies)
            return (1);
        map->enemies->prev = NULL;
        map->enemies->id = 0;
        tmp = map->enemies;
    } else {
        for(tmp = map->enemies; tmp->next; tmp = tmp->next);
        tmp->next = malloc(sizeof(enemy_t));
        if (!tmp->next)
            return (1);
        tmp->next->prev = tmp;
        tmp->next->id = tmp->id + 1;
        tmp = tmp->next;
    }
    tmp->next = NULL;
    return (setup_enemies(map, type, tmp));
}

void destroy_enemy(enemy_t *enemy, map_t *map)
{
    enemy_t **tmp = &map->enemies;

    for (; tmp[0]->id != enemy->id; tmp[0] = tmp[0]->next);
    if (tmp[0]->prev && tmp[0]->next) {
        tmp[0]->prev->next = tmp[0]->next;
        tmp[0]->next->prev = tmp[0]->prev;
    }
    else if (tmp[0]->prev)
        tmp[0]->prev->next = NULL;
    else if(tmp[0]->next) {
        tmp[0]->next->prev = NULL;
        map->enemies = tmp[0]->next;
    }
}
