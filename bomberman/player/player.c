//
// Created by Timothy Friberg Holmsten on 19/04/16.
//
#include <SDL_events.h>
#include "player.h"
#include "../game/game.h"

void create_player(Dlist *list,int *playerCount, int x, int y, int id, int playerImage)
{
    printf("%d\n", *playerCount);
    dlist_insert_last(list, dlist_createElement(id,x,y,playerImage));
    *playerCount+=1;
}

void player_place_bomb(DlistElement * player, Game *game, int x, int y)
{
    //If we were to introduce powerups MAX_BOMBS would be changed to player->maxBombs,
    //this way handling powerups for individual player would be really easy
    for(int bomb = 0; bomb < GAME_MAX_BOMBS; bomb++) {

        if (player->bombs[bomb].placed == 0) {
            player->bombs[bomb] = create_bomb(x, y, 1, player->id, player->bomb_radius);
            player->bombs_count += 1;
            player->bombs[bomb].placed = 1;

            if(player->local == 1) { // If it was the local player
                char msg[100]; // Send this to connected device
                sprintf(msg, "4 %d %d %d \n", player->id, x, y);
                client_send(game, msg);
            }
            return;
        }
    }
}

void send_player_pos(Game *game){
    char msg[100]; // Send this to connected device
    DlistElement *player;
    player = get_list_postition(&game->players, 0);
    sprintf(msg, "2 %d %d %d %d %d \n", player->id, (int)player->anix, (int)player->aniY, player->rotation, player->moving);
    client_send(game, msg);
}

void update_local_player(DlistElement * player, Map * map, Game *game, Uint32 *playerUpdate) {

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int x = 0;
    int y = 0;

    if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]){
        y = 1 * 32;
        player->rotation = 0;
    }
    if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]) {
        y = -1 * 32;
        player->rotation = 1;
    }
    if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
        x = -1 * 32;
        player->rotation = 3;
    }
    if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
        x = 1 * 32;
        player->rotation = 2;
    }

    if (state[SDL_SCANCODE_SPACE]) {
        player_place_bomb(player, game, player->x, player->y);
        SDL_Delay(16);

    }
    if(player!= NULL) {
        if (!map_is_blocked(map, player->x + x/32, player->y) && x != 0) {
            player->moving = 1;
            *playerUpdate = 0;
            for(int i = 0; i<8; i++){
                player->anix += x/8;
                send_player_pos(game); // Sends position whenever player moves to server
                SDL_Delay(15);
            }
            player->x = (int)player->anix/32;
        }

        if (!map_is_blocked(map, player->x, player->y+ y/32) && y != 0) {
            player->moving = 1;
            *playerUpdate = 0;
            for(int i = 0; i<8; i++){
                player->aniY += y/8;
                send_player_pos(game); // Sends position whenever player moves to server
                SDL_Delay(15);
            }
            player->y = (int)player->aniY/32;
        }
        if (get_object_from_position(game->map, player->x, player->y) == 9)
        {
            char msg[100]; // Send this to connected device
            sprintf(msg, "7 %d\n", get_list_postition(&game->players, 0)->id); //sends death to server
            client_send(game, msg);
            get_list_postition(&game->players, 0)->alive = 0;

        }
        player->moving = 0;

        //This stops the animations when they player stops moving
        if(player->moving == 0 && *playerUpdate == 0){
            send_player_pos(game); // Sends position whenever player moves to server
            *playerUpdate = 1;
        }
    }
}





