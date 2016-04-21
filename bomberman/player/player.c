//
// Created by Timothy Friberg Holmsten on 19/04/16.
//
#include <SDL_timer.h>
#include "player.h"
#include "../map/map.h"

Player create_player(float x, float y, int id)
{
    Player ply;
    ply.x = x;
    ply.y = y;
    ply.id = id;

    return ply;
}

void update_players(Player *players) {

}

void update_local_player(Player *player, Map map) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    float x = 0;
    float y = 0;


    if (state[SDL_SCANCODE_A])
        x = -1;
    if (state[SDL_SCANCODE_D])
        x =  1;
    if (state[SDL_SCANCODE_S])
        y =  1;
    if (state[SDL_SCANCODE_W])
        y = -1;

    if(!map_is_blocked(map, player->x + x, player->y))
        player->x += x;

    if (!map_is_blocked(map, player->x, player->y + y))
        player->y += y;

    SDL_Delay(100);

}





