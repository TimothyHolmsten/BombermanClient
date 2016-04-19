//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "renderObject.h"

void render_walls(SDL_Renderer *renderer, Wall * walls)
{
    int i = 0;

    while (i < 16)
    {
        SDL_Rect rect = {walls[i].x * 32, walls[i].y * 32, 32, 32};
        SDL_SetRenderDrawColor(renderer, 150,150,150,255);
        SDL_RenderFillRect(renderer, &rect);

        i++;
    }
}
