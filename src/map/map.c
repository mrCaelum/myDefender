/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Map
*/

#include "map.h"

map_element_t *get_map_element(map_t *map, element_id_t id)
{
    for (unsigned int y = 0, x = 0; y < map->size.y; x++) {
        if (x >= map->size.x) {
            x = -1;
            y++;
        } else if (map->tab[y][x] && map->tab[y][x]->id == id)
            return (map->tab[y][x]);
    }
    return (NULL);
}
