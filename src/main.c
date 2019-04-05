/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Main file
*/

#include <textures.h>
#include <map.h>
#include <menu.h>
#include <scene.h>
#include <options.h>
#include <zconf.h>
#include <fcntl.h>
#include "game.h"

static int game_loop(sfRenderWindow *window, sfTexture **texture,
    char const *file)
{
    game_t *game = init_game(window, texture, file, NULL);
    sfClock *clock = sfClock_create();
    scene_t scene = MENU;

    if (!game)
        return (84);
    while (sfRenderWindow_isOpen(window)) {
        if (scene == OPTIONS)
            scene_options(&window,
                sfClock_restart(clock).microseconds / 1000.f, &scene, &game);
        else
            call_scene(window,
                sfClock_restart(clock).microseconds / 1000.f, &scene, game);
    }
    destroy_game(game);
    return (0);
}

int main(int argc, char const *argv[])
{
    sfRenderWindow *window = create_window((sfVector2u){0, 0}, 1);
    sfTexture **texture;
    unsigned int seed;
    int fd = open("/dev/urandom", O_RDONLY);

    if (fd <= 0)
        return (84);
    read(fd, &seed, sizeof seed);
    srand(seed);
    close(fd);
    if (!window)
        return (84);
    texture = init_textures();
    if (!texture)
        return (84);
    return (game_loop(window, texture, argc > 1 ? argv[1] : NULL));
}
