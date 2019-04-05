/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Textures
*/

#ifndef TEXTURES_H_
    #define TEXTURES_H_

    #include <malloc.h>
    #include <SFML/Graphics.h>

typedef enum textures {
    TEX_FIELD,
    TEX_ROAD,
    TEX_PORTAL,
    TEX_CASTLE,
    TEX_COIN,
    TEX_TOWER,
    TEX_SPIKE_TOWER,
    TEX_ICE_TOWER,
    TEX_FIRE_TOWER,
    TEX_TOWER_HEAD,
    TEX_SPIKE_TOWER_HEAD,
    TEX_ICE_TOWER_HEAD,
    TEX_FIRE_TOWER_HEAD,
    TEX_BGMENU,
    TEX_TOWER_PREVIEW,
    TEX_SPIKE_TOWER_PREVIEW,
    TEX_ICE_TOWER_PREVIEW,
    TEX_FIRE_TOWER_PREVIEW,
    TEX_PROJ,
    TEX_SPIKE_PROJ,
    TEX_ICE_PROJ,
    TEX_FIRE_PROJ,
    TEX_ENEMY,
    END_TEX
} textures_t;

sfTexture **init_textures(void);

#endif
