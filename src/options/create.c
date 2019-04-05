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

static char const *MUSICS[] = {
    "resources/click.wav",
    "resources/menu.ogg",
    "resources/game.ogg",
    NULL
};

static char const *TEXTS[] = {
    "options",
    "resolution",
    "1920 x 1080",
    "fps",
    "60",
    "fullscreen",
    "on",
    "sound",
    "100 / 100",
    "back",
    NULL
};

static void set_texts_pos(options_t *options, sfVector2u window_size,
    unsigned char i)
{
    sfText *text = options->text[i];
    sfVector2f pos[] = {
        {window_size.x / 2 - sfText_getGlobalBounds(text).width / 2,
            window_size.y / 6},
        {window_size.x / 16, window_size.y / 2.7 + i * window_size.y / 20},
        {window_size.x / 8 + sfText_getGlobalBounds(options->text[i]).width,
            window_size.y / 2.7 + (i - 1) * window_size.y / 20},
        {window_size.x / 16, window_size.y / 2.7 + i * window_size.y / 20},
        {window_size.x / 4 + sfText_getGlobalBounds(options->text[i]).width,
            window_size.y / 2.7 + (i - 1) * window_size.y / 20},
        {window_size.x - sfText_getGlobalBounds(text).width -
            window_size.x / 16, window_size.y -
            sfText_getGlobalBounds(text).height - window_size.y / 16}
    };
    sfText_setCharacterSize(options->text[i],
        window_size.y / (i ? 40 : 20));
    sfText_setPosition(text, pos[i == 7 ? 1 : i == 8 ? 2 : i > 2 ? i - 2 : i]);
    if (i == 9)
        options->back_pos = pos[5];
}

static void init_music(options_t *options)
{
    for (unsigned char i = 0; i < 3; i++) {
        options->music[i] = sfMusic_createFromFile(MUSICS[i]);
        if (!options->music[i])
            continue;
    }
    sfMusic_setLoop(options->music[1], sfTrue);
    sfMusic_setLoop(options->music[2], sfTrue);
}

options_t *init_options(sfTexture **texture, sfVector2u window_size,
    char const *size)
{
    options_t *options = malloc(sizeof(options_t));

    if (!options)
        return NULL;
    options->font = sfFont_createFromFile("resources/main_font.ttf");
    if (!options->font)
        return NULL;
    for (unsigned int i = 0; TEXTS[i]; i++) {
        options->text[i] = sfText_create();
        if (!options->text[i])
            return NULL;
        sfText_setFont(options->text[i], options->font);
        sfText_setString(options->text[i], (i == 2 && size) ? size : TEXTS[i]);
        set_texts_pos(options, window_size, i);
    }
    options->text[10] = NULL;
    for (unsigned char i = 0; i < 4; i++)
        options->selected[i] = 0;
    init_music(options);
    return options;
}
