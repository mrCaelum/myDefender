/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Game menu
*/

#include "textures.h"
#include "game.h"

static const unsigned int TOWER_PRICE[] = {
    70,
    80,
    90,
    140,
    0
};

static _Bool init_towers_preview(game_menu_t *menu, sfVector2u window_size)
{
    menu->towers = malloc(TOTAL_TOWERS * sizeof(sfSprite **));
    if (!menu->towers)
        return (1);
    for (int i = 0; i < TOTAL_TOWERS; i++) {
        menu->towers[i] = sfSprite_create();
        if (!menu->towers[i])
            return (1);
        sfSprite_setTexture(menu->towers[i],
            menu->texture[TEX_TOWER_PREVIEW + i], sfTrue);
        sfSprite_setScale(menu->towers[i],
            (sfVector2f){0.5, 0.5});
        sfSprite_setPosition(menu->towers[i], (sfVector2f)
        {window_size.x / 2 - 900 / 2 + (i + 1) * window_size.x / 14,
            window_size.y});
    }
    return (0);
}

game_menu_t *init_game_menu(sfTexture **texture, sfRenderWindow *window, sfMusic *music)
{
    game_menu_t *menu = malloc(sizeof(game_menu_t));
    sfVector2u window_size = sfRenderWindow_getSize(window);

    if (!menu)
        return (NULL);
    menu->window = window;
    init_money_preview(texture, menu);
    menu->background = sfSprite_create();
    if (!menu->background)
        return (NULL);
    sfSprite_setTexture(menu->background, texture[TEX_BGMENU], sfTrue);
    sfSprite_setPosition(menu->background, (sfVector2f)
    {window_size.x / 2 - 900 / 2, window_size.y - window_size.y / 54});
    menu->texture = texture;
    menu->money = 1000;
    menu->music = music;
    if (init_towers_preview(menu, window_size))
        return (NULL);
    return (menu);
}

void anim_game_menu(game_menu_t *menu, int i)
{
    static _Bool key_r = 0;
    static _Bool wait = 0;
    sfFloatRect bounds = sfSprite_getGlobalBounds(menu->background);

    if (!sfKeyboard_isKeyPressed(sfKeyI))
        wait = 1;
    else if (sfKeyboard_isKeyPressed(sfKeyI) && wait) {
        key_r = !key_r;
        wait = 0;
    }
    if ((i || key_r) && bounds.top + bounds.height - 20 > 1080) {
        sfSprite_move(menu->background, (sfVector2f){0, -16});
        for (unsigned char j = 0; j < TOTAL_TOWERS; j++)
            sfSprite_move(menu->towers[j], (sfVector2f){0, -16});
    } else if (!(i || key_r) && bounds.top + 30 < 1080) {
        sfSprite_move(menu->background, (sfVector2f){0, 16});
        for (unsigned char j = 0; j < TOTAL_TOWERS; j++)
            sfSprite_move(menu->towers[j], (sfVector2f){0, 16});
    }
}

void buy_tower(game_t *game, sfVector2i mouse)
{
    sfFloatRect bounds;

    for (unsigned char i = 0; i < TOTAL_TOWERS; i++) {
        bounds = sfSprite_getGlobalBounds(game->game_menu->towers[i]);
        if (sfFloatRect_contains(&bounds, mouse.x, mouse.y)
        && game->game_menu->money >= TOWER_PRICE[i]) {
            create_tower(i, game->map);
            game->game_menu->money -= TOWER_PRICE[i];
        }
    }
}
