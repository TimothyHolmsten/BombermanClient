//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "renderPlayer.h"

void render_players(SDL_Renderer *renderer, Player players[])
{
    int i = 0;

    while(i < 8) {
        if (players[i].x != 0 && players[i].y != 0) {
            SDL_Rect rect = {256 + players[i].x * 32, players[i].y * 32, 32, 32};
            SDL_SetRenderDrawColor(renderer, 255, 150, 150, 255);
            SDL_RenderFillRect(renderer, &rect);
        }

        i++;
    }
}