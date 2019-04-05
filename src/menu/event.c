/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Menu events
*/

#include "menu.h"

static void update_menu(menu_t *menu)
{
    for (unsigned char i = 1; i < menu->size; i++) {
        if (!menu->active[i])
            set_button_disable(menu, i);
        else if (menu->selected == i)
            set_button_hover(menu, i);
        else
            set_button_default(menu, i);
    }
}

static void mouse_event(sfEvent event, scene_t *scene, menu_t *menu,
    sfVector2i mouse)
{
    sfFloatRect bounds;
    _Bool set = 0;

    for (unsigned int i = 1; i < menu->size; i++) {
        bounds = sfText_getGlobalBounds(menu->text[i]);
        if (sfFloatRect_contains(&bounds, mouse.x, mouse.y)) {
            menu->play_sound = menu->selected == i ? menu->play_sound : 1;
            menu->selected = i;
            set = 1;
        }
    }
    if (!set)
        menu->selected = 0;
    if (event.type == 9 && menu->selected) {
        *scene = menu->scenes_tab[menu->selected - 1];
        menu->play_sound = 1;
    }
}

static void key_event(scene_t *scene, menu_t *menu)
{
    _Bool oneTime = 1;

    if (!menu->selected)
        menu->selected = 1;
    if (sfKeyboard_isKeyPressed(sfKeyReturn)) {
        *scene = menu->scenes_tab[menu->selected - 1];
        menu->play_sound = 1;
    }
    while (oneTime || !menu->active[menu->selected]) {
        oneTime = 0;
        if (sfKeyboard_isKeyPressed(sfKeyUp)) {
            menu->selected = menu->selected == 1 ?
            menu->size - 1 : menu->selected - 1;
            menu->play_sound = 1;
        } else if (sfKeyboard_isKeyPressed(sfKeyDown)) {
            menu->selected = menu->selected == menu->size - 1 ?
            1 : menu->selected + 1;
            menu->play_sound = 1;
        }
    }
}

void menu_events(sfEvent event, scene_t *scene, menu_t *menu,
    sfVector2i mouse)
{
    if (event.type == sfEvtMouseMoved && menu->select_mode) {
        menu->select_mode = 0;
        sfRenderWindow_setMouseCursorVisible(menu->window, 1);
    } else if (event.type == sfEvtKeyReleased && !menu->select_mode) {
        menu->select_mode = 1;
        sfRenderWindow_setMouseCursorVisible(menu->window, 0);
    }
    if (menu->select_mode) {
        key_event(scene, menu);
    } else {
        mouse_event(event, scene, menu, mouse);
    }
    update_menu(menu);
    if (menu->play_sound) {
        sfMusic_stop(menu->music[0]);
        sfMusic_play(menu->music[0]);
        menu->play_sound = 0;
    }
}
