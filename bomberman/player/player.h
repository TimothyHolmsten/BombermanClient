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
#include <time.h>
#include "../tools/linked_list.h"
#include "../client/client.h"
#include "../main.h"


void create_player(Dlist *list, int *playerCount, int x, int y, int id);
void player_place_bomb(DlistElement * player, Game *game,int x,int y);

void update_players(Dlist *players);
void update_local_player(DlistElement *player, Map * map,Game *game, Uint32 *playerUpdate);

#endif //CLIENT_PLAYER_H