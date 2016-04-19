#include <stdio.h>
#include <SDL.h>
#include "game/game.h"
#include "map/map.h"
#include "object/objects/wall/wall.h"

int main(void)
{
    SDL_Window *window;
    window = init_window(1024,600,"hej");

    SDL_Renderer *renderer;
    renderer = init_renderer(window);

    Wall walls[GAME_MAX_X*GAME_MAX_Y] = {0};

    Map _map;

    _map = load_map("level1.map");

    load_walls(_map, walls);



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
    int i = 0;

    while(i < 100)
    {
        printf("X: %d, Y: %d", walls[i].x, walls[i].y);
        i++;
    }

    game_loop(window, renderer, walls);

    return 0;
}