/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Money preview
*/

#include "textures.h"
#include "game.h"
#include "str.h"

void init_money_preview(sfTexture **texture, game_menu_t *menu)
{
    sfVector2u window_size = sfRenderWindow_getSize(menu->window);

    menu->money_preview = (struct money_preview_s){
        sfSprite_create(),
        sfFont_createFromFile("resources/main_font.ttf"),
        sfText_create()
    };
    sfSprite_setTexture(menu->money_preview.coin, texture[TEX_COIN], sfTrue);
    sfSprite_setTextureRect(menu->money_preview.coin,
        (sfIntRect){0, 0, 64, 64});
    sfSprite_setPosition(menu->money_preview.coin, (sfVector2f)
    {window_size.x / 19, window_size.y / 27});
    sfText_setFont(menu->money_preview.money, menu->money_preview.font);
    sfText_setString(menu->money_preview.money, "0");
    sfText_setCharacterSize(menu->money_preview.money, window_size.x / 48);
    sfText_setPosition(menu->money_preview.money, (sfVector2f)
    {window_size.x / 10, window_size.y / 22});
}

void update_money_preview(game_menu_t *menu)
{
    sfIntRect rect = sfSprite_getTextureRect(menu->money_preview.coin);
    char *str = int_to_str(menu->money);

    rect.left = rect.left >= 15 * 64 ? 0 : rect.left + 64;
    sfSprite_setTextureRect(menu->money_preview.coin, rect);
    sfText_setString(menu->money_preview.money, str);
    free(str);
}

void draw_money_preview(sfRenderWindow *window, game_menu_t *menu)
{
    sfRenderWindow_drawSprite(window, menu->money_preview.coin, NULL);
    sfRenderWindow_drawText(window, menu->money_preview.money, NULL);
}
