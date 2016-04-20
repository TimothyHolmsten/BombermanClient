//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "renderPlayer.h"

void render_players(SDL_Renderer *renderer, Player players[])
{
    int i = 0;
    int players_inGame = 2;  // Render only if player is in game
    while(i < players_inGame) {
        if (players[i].x != 0 && players[i].y != 0) {
            SDL_Rect rect = {256 + players[i].x * 32, players[i].y * 32, 32, 32};
            SDL_SetRenderDrawColor(renderer, 255, 150, 150, 255);
            SDL_RenderFillRect(renderer, &rect);
        }

        i++;
    }
}

//Control player locally, and update the other players postition
void update_players(Player players[]) {
    float speed = 0.005;
    printf("x: %f", players[2].x);
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_A]) {
        players[0].x -= speed;
    }
    if (state[SDL_SCANCODE_D]) {
        players[0].x += speed;
    }
    if (state[SDL_SCANCODE_W]) {
        players[0].y -= speed;
    }
    if (state[SDL_SCANCODE_S]) {
        players[0].y += speed;
    }
    //Multiplayer
    /*
    int players_inGame = 2; // Move to function parameter
    int i = 1; //Don't update yourself
    while (i < players_inGame) {
        if (players[i].x != 0 && players[i].y != 0) {
            // Get players x and y coordinates  from the server
            // here and put it into players x and y locally
        }
    }
     */
}