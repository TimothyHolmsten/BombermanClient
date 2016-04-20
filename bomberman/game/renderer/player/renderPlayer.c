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
void update_players(Player players[], Wall walls[]) {
    float speed = 0.005;
    bool move_up = true;
    bool move_down = true;
    bool move_right = true;

    for(int i=0; i < GAME_MAX_X*GAME_MAX_Y; i++)
    {
        // If player has same x coordinates
        if(-1 < players[0].x-walls[i].x &&   players[0].x-walls[i].x < 1)
        {
            // check if moving up is inside a block
            if(0 < players[0].y-0.02-walls[i].y &&   players[0].y-0.02-walls[i].y < 1)
            {
                move_up = false;
                break;
            }
            else
                move_up = true;
            // check if moving up is inside a block
            if(0 < players[0].y+1-walls[i].y &&   players[0].y+1-walls[i].y < 1)
            {
                move_down = false;
                break;
            }
            else
                move_down = true;
        }

        if(-1 < players[0].y-walls[i].y &&   players[0].y-walls[i].y < 1)
        {
            printf("test");
            // check if moving up is inside a block
            if(0 < players[0].x-walls[i].x &&   players[0].x-walls[i].x < 1)
            {
                move_right = false;
                break;
            }
            else
                move_right = true;

        }

    }



    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_A]) {
        players[0].x -= speed;
    }
    if (state[SDL_SCANCODE_D] && move_right == true) {
        players[0].x += speed;
    }
    if (state[SDL_SCANCODE_W] && move_up == true) {
        players[0].y -= speed;
    }
    if (state[SDL_SCANCODE_S] && move_down == true) {
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