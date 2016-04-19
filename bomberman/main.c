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

    load_map("level1.map");

    game_loop(window, renderer);

    return 0;
}