/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Towers init
*/

#include "textures.h"
#include "towers.h"

static const int TOWER_ATTACK[] = {4, 1, 0, 1};
static const float TOWER_RANGE[] = {700.0, 540.0, 500.0, 300.0};
static const char *NAMES[] = {
    "Basic",
    "Spikes",
    "Ice",
    "Fire",
    NULL
};
static const char *STATS[] = {
    "Strength",
    "Range",
    NULL
};

static void create_range_preview(tower_t *tower, map_t *map)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(tower->sprite[0]);
    sfFloatRect prev_bounds;

    for (unsigned char i = 0; i < 20; i++) {
        tower->range_preview[i] = sfCircleShape_create();
        if (!tower->range_preview[i])
            continue;
        sfCircleShape_setOutlineColor(tower->range_preview[i],
            sfColor_fromRGBA(60, 60, 60, 200 - i * 10));
        sfCircleShape_setFillColor(tower->range_preview[i], sfTransparent);
        sfCircleShape_setOutlineThickness(tower->range_preview[i], 2);
        sfCircleShape_setRadius(tower->range_preview[i],
            tower->range - i * 2);
        prev_bounds = sfCircleShape_getGlobalBounds(tower->range_preview[i]);
        sfCircleShape_setPosition(tower->range_preview[i], (sfVector2f)
        {bounds.left + bounds.width / 2 - prev_bounds.width / 2,
            bounds.top + bounds.height / 2 - prev_bounds.height / 2});
    }
}

static void init_tower_stats(_Bool type, map_t *map, tower_t *tower)
{
    tower->tower_stats.font = sfFont_createFromFile("resources/main_font.ttf");
    tower->tower_stats.title = sfText_create();
    sfText_setFont(tower->tower_stats.title, tower->tower_stats.font);
    sfText_setString(tower->tower_stats.title, NAMES[type]);
    sfText_setCharacterSize(tower->tower_stats.title, 30);
    sfText_setPosition(tower->tower_stats.title, (sfVector2f){80, 400});
    for (unsigned int i = 0; STATS[i]; i++) {
        tower->tower_stats.stat[i] = sfText_create();
        sfText_setFont(tower->tower_stats.stat[i], tower->tower_stats.font);
        sfText_setString(tower->tower_stats.stat[i], STATS[i]);
        sfText_setCharacterSize(tower->tower_stats.stat[i], 26);
        sfText_setPosition(tower->tower_stats.stat[i],
            (sfVector2f){100, 500 + i * 80});
    }
    create_range_preview(tower, map);
}

int create_tower(unsigned char type, map_t *map)
{
    tower_t *tower = malloc(sizeof(tower_t));
    sfVector2f position = (sfVector2f){(map->scaling_factor.x * 256) *
    map->selected_pos.x + map->center_factor.x, (map->scaling_factor.y * 256) *
    map->selected_pos.y + map->center_factor.y};

    for (unsigned char i = 0; i < 2; i++) {
        tower->sprite[i] = sfSprite_create();
        if (!tower->sprite[i])
            return (84);
        sfSprite_setTexture(tower->sprite[i],
            map->texture[(i ? TEX_TOWER_HEAD : TEX_TOWER) + type], sfTrue);
        sfSprite_setOrigin(tower->sprite[i], (sfVector2f){128, 128});
        sfSprite_setScale(tower->sprite[i], map->scaling_factor);
        sfSprite_setPosition(tower->sprite[i], position);
    }
    tower->strength = TOWER_ATTACK[type];
    tower->range = TOWER_RANGE[type] * map->scaling_factor.x;
    tower->type = type;
    tower->target = NULL;
    map->selected->tower = tower;
    init_tower_stats(type, map, tower);
    init_tower_functions(tower);
    tower->proj = malloc(sizeof(projectile_t));
    tower->proj->sprite = sfSprite_create();
    if (!tower->proj->sprite)
        return 1;
    sfSprite_setTexture(tower->proj->sprite, map->texture[TEX_PROJ + type], 1);
    sfSprite_setPosition(tower->proj->sprite, sfSprite_getPosition(tower->sprite[1]));
    sfSprite_setScale(tower->proj->sprite, map->scaling_factor);
    tower->proj->move = (sfVector2f) {0, 0};
    return 0;
}

void tower_destroy(tower_t *tower)
{
    sfSprite_destroy(tower->sprite[0]);
    sfSprite_destroy(tower->sprite[1]);
    free(tower);
}
