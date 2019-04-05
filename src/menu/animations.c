/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Menu animations
*/

#include "menu.h"

void set_button_default(menu_t *menu, unsigned int id)
{
    sfText_setCharacterSize(menu->text[id], 26);
    sfText_setPosition(menu->text[id], menu->pos[id]);
    sfText_setColor(menu->text[id], sfColor_fromRGB(220, 220, 220));
}

void set_button_hover(menu_t *menu, unsigned int id)
{
    sfText_setCharacterSize(menu->text[id], 36);
    sfText_setPosition(menu->text[id], (sfVector2f)
    {menu->pos[id].x + 10, menu->pos[id].y - 4});
    sfText_setColor(menu->text[id], sfWhite);
}

void set_button_disable(menu_t *menu, unsigned int id)
{
    sfText_setCharacterSize(menu->text[id], 26);
    sfText_setPosition(menu->text[id], menu->pos[id]);
    sfText_setColor(menu->text[id], sfColor_fromRGB(180, 180, 180));
}
