/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Options
*/

#include <SFML/Graphics/Types.h>
#include <scene.h>
#include <malloc.h>
#include <textures.h>
#include "game.h"
#include "options.h"

static const sizes_t sizes[] = {
    {{1920, 1080}, "1920 x 1080"},
    {{800, 600}, "800 x 600"},
    {{0, 0}, NULL}
};

static const nb_select_t fps[] = {
    {60, "60"},
    {30, "30"},
    {90, "90"},
    {0, NULL}
};

static const nb_select_t fullscreen[] = {
    {1, "on"},
    {0, "off"},
    {0, NULL}
};

static const nb_select_t sound[] = {
    {100, "100 / 100"},
    {90, "90 / 100"},
    {80, "80 / 100"},
    {70, "70 / 100"},
    {60, "60 / 100"},
    {50, "50 / 100"},
    {40, "40 / 100"},
    {30, "30 / 100"},
    {20, "20 / 100"},
    {10, "10 / 100"},
    {0, "0 / 100"},
    {0, NULL}
};

static void event_fps(sfRenderWindow **window, sfEvent event, sfVector2i mouse,
    game_t **game)
{
    options_t *options = (*game)->options;
    sfFloatRect rect = sfText_getGlobalBounds(options->text[4]);

    if (event.type == 9 && sfFloatRect_contains(&rect, mouse.x, mouse.y)) {
        options->selected[1] = fps[options->selected[1] + 1].text ?
            options->selected[1] + 1 : 0;
        sfText_setString(options->text[4],
            fps[options->selected[1]].text);
        sfRenderWindow_setFramerateLimit(*window,
            fps[options->selected[1]].nb);
    }
}

static void event_fullscreen(sfRenderWindow **window, sfEvent event,
    sfVector2i mouse, game_t **game)
{
    options_t *options = (*game)->options;
    sfFloatRect rect = sfText_getGlobalBounds(options->text[6]);

    if (event.type == 9 && sfFloatRect_contains(&rect, mouse.x, mouse.y)) {
        options->selected[2] = fullscreen[options->selected[2] + 1].text ?
            options->selected[2] + 1 : 0;
        sfText_setString(options->text[6],
            fullscreen[options->selected[2]].text);
        sfRenderWindow_destroy(*window);
        *window = create_window(sizes[options->selected[0]].size,
            fullscreen[options->selected[2]].nb);
    }
}

static void event_sound(sfRenderWindow **window, sfEvent event,
    sfVector2i mouse, game_t **game)
{
    options_t *options = (*game)->options;
    sfFloatRect rect = sfText_getGlobalBounds(options->text[8]);

    if (event.type == 9 && sfFloatRect_contains(&rect, mouse.x, mouse.y)) {
        options->selected[3] = sound[options->selected[3] + 1].text ?
            options->selected[3] + 1 : 0;
        sfText_setString(options->text[8],
            sound[options->selected[3]].text);
        sfMusic_setVolume(options->music[0], sound[options->selected[3]].nb);
        sfMusic_setVolume(options->music[1], sound[options->selected[3]].nb);
        sfMusic_setVolume(options->music[2], sound[options->selected[3]].nb);
        sfMusic_setVolume((*game)->menu->music[0],
            sound[options->selected[3]].nb);
        sfMusic_setVolume((*game)->play_menu->music[0],
            sound[options->selected[3]].nb);
        sfMusic_setVolume((*game)->pause->music[0],
            sound[options->selected[3]].nb);
    }
}

static void event_size(sfRenderWindow **window, sfEvent event,
    sfVector2i mouse, game_t **game)
{
    options_t *options = (*game)->options;
    sfFloatRect rect = sfText_getGlobalBounds(options->text[2]);

    if (event.type == 9 && sfFloatRect_contains(&rect, mouse.x, mouse.y)) {
        options->selected[0] = sizes[options->selected[0] + 1].text ?
            options->selected[0] + 1 : 0;
        sfText_setString(options->text[2],
            sizes[options->selected[0]].text);
        sfRenderWindow_destroy(*window);
        *window = create_window(sizes[options->selected[0]].size,
            fullscreen[options->selected[2]].nb);
        // destroy_game(*game);
        sfMusic_destroy((*game)->options->music[0]);
        sfMusic_destroy((*game)->options->music[1]);
        *game = init_game(*window, (*game)->map->texture, NULL,
            sizes[options->selected[0]].text);
    }
    event_fps(window, event, mouse, game);
    event_fullscreen(window, event, mouse, game);
    event_sound(window, event, mouse, game);
}

void options_events(sfRenderWindow **window, sfEvent event, scene_t *scene,
    game_t **game)
{
    options_t *options = (*game)->options;
    sfVector2i mouse = sfMouse_getPositionRenderWindow(*window);
    unsigned char id = 9;
    sfFloatRect rect = sfText_getGlobalBounds((*game)->options->text[id]);

    if (event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape)
    || (event.type == 9 && sfFloatRect_contains(&rect, mouse.x, mouse.y)))
        *scene = MENU;
    if (sfFloatRect_contains(&rect, mouse.x, mouse.y)) {
        sfText_setCharacterSize(options->text[id], 36);
        sfText_setPosition(options->text[id], (sfVector2f)
        {options->back_pos.x - 10, options->back_pos.y - 4});
        sfText_setColor(options->text[id], sfWhite);
    } else {
        sfText_setCharacterSize(options->text[id], 26);
        sfText_setPosition(options->text[id], options->back_pos);
        sfText_setColor(options->text[id], sfColor_fromRGB(220, 220, 220));
    }
    event_size(window, event, mouse, game);
}
