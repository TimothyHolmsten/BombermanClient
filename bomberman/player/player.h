//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H

#include <SDL_types.h>
#include <SDL_system.h>
#include "../map/map.h"

typedef struct Player{
    int x;
    int y;
    int id;
} Player;

Player create_player(int x, int y, int id);

void update_players(Player players[]);
void update_local_player(Player *player, Map map);

#endif //CLIENT_PLAYER_H