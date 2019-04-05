/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Textures
*/

#include "textures.h"

static const char *textures_files_tab[] = {
    "resources/field.png",
    "resources/road.png",
    "resources/portal.png",
    "resources/castle.png",
    "resources/coin.png",
    "resources/basic_tower.png",
    "resources/spike_tower.png",
    "resources/ice_tower.png",
    "resources/fire_tower.png",
    "resources/basic_tower_head.png",
    "resources/spike_tower_head.png",
    "resources/ice_tower_head.png",
    "resources/fire_tower_head.png",
    "resources/bgmenu.png",
    "resources/basic_tower_preview.png",
    "resources/spike_tower_preview.png",
    "resources/ice_tower_preview.png",
    "resources/fire_tower_preview.png",
    "resources/basic_proj.png",
    "resources/spike_proj.png",
    "resources/ice_proj.png",
    "resources/fire_proj.png",
    "resources/enemy.png",
    NULL
};

sfTexture **init_textures(void)
{
    sfTexture **texture = malloc(END_TEX * sizeof(sfTexture **));

    for (int i = 0; i < END_TEX; i++)
        texture[i] = sfTexture_createFromFile(textures_files_tab[i], NULL);
    return (texture);
}
