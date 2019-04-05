/*
** EPITECH PROJECT, 2019
** csfml-lib
** File description:
** Window
*/

#include <SFML/Graphics.h>
#include "game.h"

sfRenderWindow *create_window(sfVector2u size, _Bool fsn)
{
    sfVideoMode screen = (sfVideoMode)
    {size.x ? size.x : 1920, size.y ? size.y : 1080, 32};
    sfRenderWindow *window = sfRenderWindow_create(screen, "my_defender",
    sfTitlebar | sfClose | (fsn ? sfFullscreen : 0), NULL);

    if (!window)
        return (NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    sfRenderWindow_setVerticalSyncEnabled(window, sfTrue);
    return (window);
}
