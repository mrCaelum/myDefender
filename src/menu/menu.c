/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Menu
*/

#include "menu.h"

static char const *MUSICS[] = {
    "resources/click.wav",
    "resources/menu.ogg",
    NULL
};

static _Bool init_text(menu_t *menu, char const *str_tab[],
    sfVector2u window_size)
{
    menu->font = sfFont_createFromFile("resources/main_font.ttf");
    menu->text = malloc((menu->size + 1) * sizeof(sfText *));
    menu->pos = malloc(menu->size * sizeof(sfVector2f));
    if (!menu->font || !menu->text)
        return (1);
    for (unsigned int i = 0; i < menu->size; i++) {
        menu->text[i] = sfText_create();
        if (!menu->text[i])
            return (1);
        sfText_setFont(menu->text[i], menu->font);
        sfText_setString(menu->text[i], str_tab[i]);
        sfText_setCharacterSize(menu->text[i], window_size.y / (i ? 40 : 20));
        menu->pos[i] = (sfVector2f){i ? window_size.x / 16 :
        window_size.x / 2 - sfText_getGlobalBounds(menu->text[i]).width / 2,
        i ? window_size.y / 2.7 + i * window_size.y / 12 : window_size.y / 6};
        sfText_setPosition(menu->text[i], menu->pos[i]);
    }
    menu->text[menu->size] = NULL;
    return (0);
}

static _Bool init_music(menu_t *menu, sfMusic *menu_music)
{
    for (unsigned char i = 0; i < 2; i++) {
        menu->music[i] = (!i || !menu_music) ?
            sfMusic_createFromFile(MUSICS[i]) : menu_music;
        if (!menu->music[i])
            return (1);
    }
    if (!menu_music)
        sfMusic_setLoop(menu->music[1], sfTrue);
    return (0);
}

menu_t *init_menu(sfRenderWindow *window, char const *str_tab[],
    scene_t const *scenes_tab, sfMusic *menu_music)
{
    menu_t *menu = malloc(sizeof(menu_t));
    sfVector2u window_size = sfRenderWindow_getSize(window);

    for (menu->size = 0; str_tab[menu->size]; menu->size++);
    menu->window = window;
    menu->active = malloc(menu->size * sizeof(unsigned char));
    for (unsigned char i = 0; i < menu->size; i++)
        menu->active[i] = 1;
    if (init_text(menu, str_tab, window_size) || init_music(menu, menu_music))
        return (NULL);
    menu->select_mode = 0;
    menu->selected = 1;
    menu->play_sound = 0;
    menu->scenes_tab = scenes_tab;
    return (menu);
}

void destroy_menu(menu_t *menu)
{
    for (unsigned int i = 0; i < menu->size; i++)
        sfText_destroy(menu->text[i]);
    free(menu->text);
    sfFont_destroy(menu->font);
    sfMusic_destroy(menu->music[0]);
    free(menu);
}
