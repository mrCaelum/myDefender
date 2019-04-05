/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Map elements
*/

#include <map.h>
#include <malloc.h>
#include <textures.h>
#include "game.h"

static map_element_t *create_new(element_id_t id, sfTexture *texture,
    sfVector2u pos, map_t *map)
{
    map_element_t *new_element = malloc(sizeof(map_element_t));
    sfVector2f position = (sfVector2f)
    {(256 * map->scaling_factor.x) * pos.x + map->center_factor.x,
        (256 * map->scaling_factor.y) * pos.y + map->center_factor.y};

    if (!new_element)
        return (NULL);
    new_element->id = id;
    new_element->sprite = sfSprite_create();
    if (!new_element->sprite)
        return (NULL);
    sfSprite_setOrigin(new_element->sprite, (sfVector2f){128, 128});
    sfSprite_setTexture(new_element->sprite, texture, sfTrue);
    sfSprite_setPosition(new_element->sprite, position);
    sfSprite_setScale(new_element->sprite, map->scaling_factor);
    new_element->tower = NULL;
    return (new_element);
}

map_element_t *create_field(map_t *map, sfTexture **texture, sfVector2u pos)
{
    map_element_t *new_element = create_new(FIELD, texture[TEX_FIELD], pos,
        map);

    if (!new_element)
        return (NULL);
    sfSprite_setTextureRect(new_element->sprite, (sfIntRect){0, 0, 256, 256});
    return (new_element);
}

map_element_t *create_road(map_t *map, sfTexture **texture, sfVector2u pos)
{
    map_element_t *new_element = create_new(ROAD, texture[TEX_ROAD], pos,
        map);

    if (!new_element)
        return (NULL);
    return (new_element);
}

map_element_t *create_portal(map_t *map, sfTexture **texture, sfVector2u pos)
{
    map_element_t *new_element = create_new(PORTAL, texture[TEX_PORTAL], pos,
        map);

    if (!new_element)
        return (NULL);
    return (new_element);
}

map_element_t *create_castle(map_t *map, sfTexture **texture, sfVector2u pos)
{
    map_element_t *new_element = create_new(CASTLE, texture[TEX_CASTLE], pos,
        map);

    if (!new_element)
        return (NULL);
    if (!map->life_preview)
        map->life_preview = sfRectangleShape_create();
    if (map->life_preview) {
        sfRectangleShape_setFillColor(map->life_preview, sfRed);
        sfRectangleShape_setSize(map->life_preview, (sfVector2f)
        {256 * map->scaling_factor.x, 16 * map->scaling_factor.x});
        sfRectangleShape_setPosition(map->life_preview, (sfVector2f){(256 *
        map->scaling_factor.x) * pos.x + map->center_factor.x - (128 *
        map->scaling_factor.x), (256 * map->scaling_factor.y) * pos.y +
        map->center_factor.y - (128 * map->scaling_factor.y)});
    }
    return (new_element);
}
