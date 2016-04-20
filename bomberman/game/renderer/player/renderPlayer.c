//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "renderPlayer.h"

void render_players(SDL_Renderer *renderer, Player players[])
{
    int i = 0;
    int players_inGame = 2;  // Render only if player is in game
    while(i < players_inGame) {
            SDL_Rect rect = {256 + players[i].x * 32, players[i].y * 32, 32, 32};
            SDL_SetRenderDrawColor(renderer, 255, 150, 150, 255);
            SDL_RenderFillRect(renderer, &rect);

        i++;
    }
}


static float roundFloat(float f){
    if (f < 0)
        f= (int) (f-0.5);
    else
        f = (int) (f+0.5);
    return f;
}


void collision_detection(Player *players, Wall *walls, bool *move_up,bool *move_down,bool *move_right,bool *move_left)
{
    for(int i=0; i < GAME_MAX_X*GAME_MAX_Y; i++) {

        if(players[0].y - walls[i].y == 0)
        {
            // check if moving up is inside a block
            if(players[0].x + 1 - walls[i].x == 0)
                *move_right = false;
            if(players[0].x - 1 - walls[i].x == 0)
                *move_left = false;
        }
        // If player has same x coordinates as wall
        if (players[0].x - walls[i].x == 0) {
            // check if moving up is inside a block
            if (players[0].y - 1 - walls[i].y == 0)
                *move_up = false;
            if (players[0].y + 1 - walls[i].y == 0)
                *move_down = false;
        }
    }
}

//Control player locally, and update the other players postition
void update_players(Player players[], Wall walls[]) {
    int speed = 15;
    bool move_up = true;
    bool move_down = true;
    bool move_right = true;
    bool move_left = true;


    collision_detection(players,walls,&move_up,&move_down, &move_right,&move_left);

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_A] && move_left == true) {
            for (int i = 0; i < 10; i++) {
                players[0].x -= 0.10;
                SDL_Delay(speed);
            }
            players[0].x= roundFloat(players[0].x);
        }
        if (state[SDL_SCANCODE_D] && move_right == true) {
            for (int i = 0; i < 10; i++) {
                players[0].x += 0.1;
                SDL_Delay(speed);
            }
            players[0].x= roundFloat(players[0].x);

        }
    collision_detection(players,walls,&move_up,&move_down, &move_right,&move_left);
        if (state[SDL_SCANCODE_W] && move_up == true) {
            for (int i = 0; i < 10; i++) {
                players[0].y -= 0.1;
                SDL_Delay(speed);
            }
            players[0].y= roundFloat(players[0].y);

        }
        if (state[SDL_SCANCODE_S] && move_down == true) {

            for (int i = 0; i < 10; i++) {
                players[0].y += 0.1;
                SDL_Delay(speed);
            }
            players[0].y= roundFloat(players[0].y);

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
