#include <stdio.h>
#include <SDL.h>
#include "game/game.h"
#include "map/map.h"
#include "object/objects/wall/wall.h"

int main(void)
{
    SDL_Window *window;
    window = init_window(500,500,"hej");

    SDL_Renderer *renderer;
    renderer = init_renderer(window);

    Map _map;

    _map = load_map("level1.map");

    Wall * walls = load_walls(_map);

    printf("%d", walls[10].y);

    /* GOOD STUFF
    for (int i = 0; i < GAME_MAX_Y; i++)
    {
        for(int j = 0; j < GAME_MAX_X; j++)
        {
            printf("%d",_map.map_array[j][i]);
        }
        printf("\n");
    }
     */



    game_loop(window, renderer);

    return 0;
}