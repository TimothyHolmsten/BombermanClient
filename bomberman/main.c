#include <stdio.h>
#include <SDL.h>
#include "game/game.h"
#include "map/map.h"

int main(void)
{
    SDL_Window *window;
    window = init_window(500,500,"hej");

    SDL_Renderer *renderer;
    renderer = init_renderer(window);

    Map _map;

    _map = load_map("level1.map");


    /* GOOD STUFF
    for (int i = 0; i < MAX_Y; i++)
    {
        for(int j = 0; j < MAX_X; j++)
        {
            printf("%d",_map.map_array[j][i]);
        }
        printf("\n");
    }
     */

    game_loop(window, renderer);

    return 0;
}