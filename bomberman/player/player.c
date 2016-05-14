//
// Created by Timothy Friberg Holmsten on 19/04/16.
//
#include <SDL_events.h>
#include "player.h"
#include "../game/game.h"

void create_player(Dlist *list,int *playerCount, int x, int y, int id)
{
    printf("%d\n", *playerCount);
    dlist_insert_last(list, dlist_createElement(id,x,y));
    *playerCount+=1;
}

void update_players(Dlist * players) {

}

void player_place_bomb(DlistElement * player, Game *game, int x, int y)
{

    for(int bomb = 0; bomb < GAME_MAX_BOMBS;bomb++) {
        if (player->bombs[bomb].placed != 1) {
            player->bombs[bomb] = create_bomb(x, y, 1, player->id, 3);
            player->bombs_count += 1;
            player->bombs[bomb].placed = 1;

            if(player->local == 1) {
                char msg[100]; // Send this to connected device
                sprintf(msg, "4 %d %d %d \n", get_list_postition(&game->players, 0)->id, x, y);
                client_send(game, msg);
            }
                break;
        }
    }
}


void send_player_pos(Game *game){
    char msg[100]; // Send this to connected device
    sprintf(msg, "2 %d %d %d \n", get_list_postition(&game->players, 0)->id, (int)get_list_postition(&game->players, 0)->anix, (int)get_list_postition(&game->players, 0)->aniY);
    client_send(game, msg);
}



void update_local_player(DlistElement * player, Map * map, Game *game) {

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int x = 0;
    int y = 0;

    if (state[SDL_SCANCODE_A])
        x = -1*32;
    if (state[SDL_SCANCODE_D])
        x =  1*32;
    if (state[SDL_SCANCODE_S])
        y =  1*32;
    if (state[SDL_SCANCODE_W])
        y = -1*32;
    if (state[SDL_SCANCODE_SPACE])
        player_place_bomb(player, game,player->x,player->y);

    if(player!= NULL) {
        if (!map_is_blocked(map, player->x + x/32, player->y) && x != 0) {

            for(int i = 0; i<8; i++){
                player->anix += x/8;
                send_player_pos(game); // Sends position whenever player moves to server
                SDL_Delay(10);
            }
            player->x = (int)player->anix/32;
        }

        if (!map_is_blocked(map, player->x, player->y+ y/32) && y != 0) {

            for(int i = 0; i<8; i++){
                player->aniY += y/8;
                send_player_pos(game); // Sends position whenever player moves to server
                SDL_Delay(10);
            }
            player->y = (int)player->aniY/32;
        }

        if (get_object_from_position(game->map, player->x, player->y) == 9)
        {
            char msg[100]; // Send this to connected device
            sprintf(msg, "7 %d\n", get_list_postition(&game->players, 0)->id); //sends death to server
            get_list_postition(&game->players, 0)->alive = 0;

        }

        //This is to make sure that all clients has the most recent postition without having to flood
        // the server with postions all the time. If any client has any lag and misses an update this will
        // fix it and allways keep everyone updated.

    }
    //SDL_Delay(200);
}





