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

/* Creates a player with given arguments and inserts it into a linked list
 * Updates the player count
 * */
void create_player(Dlist *list, int *playerCount, int x, int y, int id,int playerImage);
/* Checks if the player can place a bomb or not
 * Sends a message to the server that there was a bomb placed
 * */
void player_place_bomb(DlistElement * player, Game *game,int x,int y);
/* Used by a thread to update the local player
 * Checks what buttons are pressed
 * Sends player position to the server
 * */
void update_local_player(DlistElement *player, Map * map,Game *game, Uint32 *playerUpdate);
void send_player_pos(Game *game)
#endif //CLIENT_PLAYER_H