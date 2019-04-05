/*
** EPITECH PROJECT, 2019
** MUL_my_defender_2018
** File description:
** Game
*/

#include "scene.h"
#include "map.h"
#include "game.h"
#include "textures.h"

static void update_enemies(float elapsed, map_t *map)
{
    static float enemy_launch = 0;
    static float enemies_move =  0;

    enemy_launch += elapsed;
    if (enemy_launch > 2000) {
        init_enemy(0, map);
        enemy_launch -= 2000;
    }
    enemies_move += elapsed;
    if (enemies_move > 10) {
        move_enemy(map);
        enemies_move -= 10;
    }
}

static void update(float elapsed, map_t *map, game_menu_t *game_menu)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(game_menu->window);
    sfFloatRect bounds = sfSprite_getGlobalBounds(game_menu->background);
    static float clock_money = 0;
    static float tower_clock = 0;
    static float proj_clock = 0;

    update_enemies(elapsed, map);
    clock_money += elapsed;
    if (clock_money > 100) {
        update_money_preview(game_menu);
        clock_money -= 100;
    }
    tower_clock += elapsed;
    proj_clock += elapsed;
    if (proj_clock > 1000) {
        for (unsigned int y = 0, x = 0; y < map->size.y; x++) {
            if (x >= map->size.x) {
                x = -1;
                y++;
            } else if (map->tab[y][x] && map->tab[y][x]->tower)
                move_projectiles(map->tab[y][x]->tower, elapsed);
        }
        proj_clock -= 1000;
    }
    if (tower_clock > 10) {
        update_towers(map);
        anim_game_menu(game_menu, sfFloatRect_contains(&bounds, mouse.x, mouse.y));
        sfRectangleShape_setSize(map->life_preview, (sfVector2f)
        {map->hp * 0.256 * map->scaling_factor.x, 16 * map->scaling_factor.y});
        tower_clock -= 10;
    }
}

static void draw(sfRenderWindow *window, map_t *map, game_menu_t *game_menu)
{
    sfRenderWindow_clear(window, sfBlack);
    for (unsigned int y = 0, x = 0; y < map->size.y; x++) {
        if (x >= map->size.x) {
            x = -1;
            y++;
        } else if (map->tab[y][x]) {
            sfRenderWindow_drawSprite(window, map->tab[y][x]->sprite, NULL);
            draw_tower(window, map->tab[y][x]->tower);
        }
    }
    sfRenderWindow_drawRectangleShape(window, map->life_preview, NULL);
    draw_enemies(window, map);
    sfRenderWindow_drawSprite(window, game_menu->background, NULL);
    for (unsigned int i = 0; i < TOTAL_TOWERS; i++)
        sfRenderWindow_drawSprite(window, game_menu->towers[i], NULL);
    if (map->selected && map->selected->tower && map->selected->tower->range_preview)
        for (unsigned char i = 0; i < 20; i++)
            sfRenderWindow_drawCircleShape(window,
                map->selected->tower->range_preview[i], NULL);
    draw_money_preview(window, game_menu);
    sfRenderWindow_display(window);
}

void scene_game(sfRenderWindow *window, float elapsed, scene_t *scene,
    game_t *game)
{
    sfEvent event;

    if (sfMusic_getStatus(game->game_menu->music) != sfPlaying)
        sfMusic_play(game->game_menu->music);
    while (sfRenderWindow_pollEvent(window, &event))
        game_events(window, event, game, scene);
    update(elapsed, game->map, game->game_menu);
    if (*scene != GAME)
        sfMusic_pause(game->game_menu->music);
    draw(window, game->map, game->game_menu);
}
