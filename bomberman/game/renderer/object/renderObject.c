//
// Created by Timothy Friberg Holmsten on 19/04/16.
//


#include "renderObject.h"

void render_walls(SDL_Window *window, Wall walls[GAME_MAX_X*GAME_MAX_Y])
{
    int i = 0;
    SDL_Renderer *renderer = SDL_GetRenderer(window);

    SDL_Texture *texture;
    texture = load_texture(renderer,"Wall.png");

    while(i < GAME_MAX_X*GAME_MAX_Y) {
        SDL_Rect rect = {256 + walls[i].x * 32, walls[i].y * 32, 32, 32};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        i++;
    }
}
