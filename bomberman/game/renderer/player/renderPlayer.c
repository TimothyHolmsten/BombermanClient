//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "renderPlayer.h"

void render_players(SDL_Window *window, Player players[])
{
    SDL_Renderer *renderer = SDL_GetRenderer(window);

    int i = 0;
    int players_inGame = 2;  // Render only if player is in game
    while(i < players_inGame) {
            SDL_Rect rect = {256 + players[i].x * 32, players[i].y * 32, 32, 32};
            SDL_SetRenderDrawColor(renderer, 255, 150, 150, 255);
            SDL_RenderFillRect(renderer, &rect);

        i++;
    }
}

