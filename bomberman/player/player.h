//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H

#include <SDL_types.h>
#include <SDL_system.h>
#include "../map/map.h"
#include "../object/objects/bomb/bomb.h"
#include <SDL_timer.h>

typedef struct player{
    int x;
    int y;
    int id;
    Bomb bombs[2];
    int bombs_count;
} Player;

Player create_player(int x, int y, int id);

void update_players(Player players[]);
void update_local_player(Player *player, Map map);

#endif //CLIENT_PLAYER_H