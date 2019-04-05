/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Map
*/

#include <unistd.h>
#include <map.h>
#include <fcntl.h>
#include <malloc.h>
#include "game.h"

static const struct map_create_tab_s map_elements_tab[] = {
    {' ', NULL},
    {'#', &create_field},
    {'R', &create_road},
    {'~', &create_portal},
    {'@', &create_castle},
    {0, NULL}
};

static int check_character(char c)
{
    if (c == '\n')
        return (0);
    for (unsigned int i = 0; map_elements_tab[i].character; i++)
        if (map_elements_tab[i].character == c)
            return (0);
    return (1);
}

static sfVector2u check_map(char const *filename, unsigned int *readed)
{
    sfVector2u size = (sfVector2u){0, 0};
    int fd = open(filename, O_RDONLY);
    char buffer[MAX_MAP_SIZE];
    unsigned int counter = 0;

    if (fd == -1 || (*readed = read(fd, buffer, MAX_MAP_SIZE)) < 32)
        return (size);
    for (unsigned int i = 0; i < *readed; i++) {
        if (check_character(buffer[i]))
            return ((sfVector2u){0, 0});
        if (buffer[i] == '\n') {
            size.x = counter > size.x ? counter : size.x;
            size.y++;
            counter = 0;
        } else
            counter++;
    }
    close(fd);
    return (size);
}

static map_element_t *create_new_element(char c, sfTexture **texture,
    map_t *map, sfVector2u pos)
{
    for (unsigned int i = 0; map_elements_tab[i].character; i++)
        if (map_elements_tab[i].character == c)
            return (map_elements_tab[i].create(map, texture, pos));
    return (NULL);
}

static int fill_map(map_t *map, char const *filename, unsigned int buffer_size,
    sfTexture **texture)
{
    int fd = open(filename, O_RDONLY);
    char buffer[MAX_MAP_SIZE];

    if (fd == -1 || buffer_size != read(fd, buffer, MAX_MAP_SIZE))
        return (1);
    for (unsigned int y = 0; y < map->size.y; y++)
        for (unsigned int x = 0; x < map->size.x; x++)
            map->tab[y][x] = NULL;
    for (unsigned int i = 0, y = 0, x = 0; i < buffer_size; i++, x++) {
        if (buffer[i] == '\n') {
            y++;
            x = -1;
        } else if (buffer[i] != ' ')
            map->tab[y][x] = create_new_element(buffer[i], texture,
                map, (sfVector2u){x, y});
    }
    close(fd);
    return (0);
}
//TODO: norm
map_t *map_create_from_file(char const *filename, sfTexture **texture,
    sfVector2u window_size)
{
    map_t *map = malloc(sizeof(map_t));
    float scale;
    unsigned int buffer_size;

    if (!map)
        return (NULL);
    map->size = check_map(filename, &buffer_size);
    if (map->size.x < 8 && map->size.y < 6)
        return (free(map), NULL);
    scale = LOWER((float)(window_size.x - 128) / (float)(map->size.x * 256),
        (float)(window_size.y - 128) / (float)(map->size.y * 256));
    map->scaling_factor = (sfVector2f){scale, scale};
    map->center_factor = (sfVector2f)
    {window_size.x / 6 + (window_size.x - 384 * scale * map->size.x) / 2,
        window_size.y / 4 + (window_size.y - 384 * scale * map->size.y) / 2};
    map->texture = texture;
    map->selected = NULL;
    map->enemies = NULL;
    map->hp = 1000;
    map->life_preview = NULL;
    map->tab = malloc(map->size.y * sizeof(map_element_t **));
    if (!map->tab)
        return (NULL);
    for (unsigned int y = 0; y < map->size.y; y++) {
        map->tab[y] = malloc(map->size.x * sizeof(map_element_t *));
        if (!map->tab[y])
            return (NULL);
    }
    if (fill_map(map, filename, buffer_size, texture))
        return (NULL);
    return (map);
}
