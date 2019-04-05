/*
** EPITECH PROJECT, 2018
** menu.h
** File description:
**
*/
#ifndef MY_DEFENDER_MENU_H
    #define MY_DEFENDER_MENU_H

    #include <stdlib.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio/Music.h>
    #include "scene.h"

    struct menu_s;
    typedef enum scene scene_t;

    typedef struct menu_s {
        sfRenderWindow *window;
        sfFont *font;
        sfText **text;
        sfVector2f *pos;
        unsigned char *active;
        unsigned int size;
        sfMusic *music[2];
        _Bool select_mode;
        unsigned int selected;
        _Bool play_sound;
        scene_t const *scenes_tab;
    } menu_t;

    menu_t *init_menu(sfRenderWindow *, char const *[], scene_t const *,
        sfMusic *);

    void menu_events(sfEvent, scene_t *, menu_t *, sfVector2i);

    void destroy_menu(menu_t *);

    void set_button_default(menu_t *, unsigned int);
    void set_button_hover(menu_t *, unsigned int);
    void set_button_disable(menu_t *, unsigned int);

#endif //MY_DEFENDER_MENU_H
