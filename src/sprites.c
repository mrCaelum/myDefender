/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Sprites
*/

#include "sprite_tools.h"

sfVector2f get_middle_pos(sfSprite *sprite)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(sprite);

    return (sfVector2f)
    {bounds.left + bounds.width / 2, bounds.top + bounds.height / 2};
}
