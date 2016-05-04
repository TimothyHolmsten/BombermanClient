//
// Created by Timothy Friberg Holmsten on 19/04/16.
//
#include <SDL_events.h>
#include "player.h"
#include "../game/game.h"

Player create_player(int x, int y, int id)
{
    Player ply;
    ply.x = x;
    ply.y = y;
    ply.id = id;

    return ply;
}

void update_players(Player * players) {

}

void player_place_bomb(Player * player, Map * map)
{
    for(int bomb = 0; bomb < GAME_MAX_BOMBS;bomb++) {
        if (player->bombs[bomb].placed != 1) {
            player->bombs[bomb] = create_bomb(player->x, player->y, 1, player->id);
            player->bombs[bomb].order = GAME_MAX_BOMBS-1-bomb;
            player->bombs_count += 1;
            player->bombs[bomb].placed = 1;
            SDL_Delay(100);
            break;
        }
    }
}

void update_local_player(Player *player, Map * map) {

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    int x = 0;
    int y = 0;

    if (state[SDL_SCANCODE_A])
        x = -1;
    if (state[SDL_SCANCODE_D])
        x =  1;
    if (state[SDL_SCANCODE_S])
        y =  1;
    if (state[SDL_SCANCODE_W])
        y = -1;
    if (state[SDL_SCANCODE_SPACE])
        player_place_bomb(player, map);

    if(!map_is_blocked(map, player->x + x, player->y) && x != 0)
    {
        player->x += x;
    }

    if (!map_is_blocked(map, player->x, player->y + y) && y != 0)
    {
        player->y += y;
    }
    if (x != 0 || y != 0)
        SDL_Delay(100);

    //SDL_Delay(200);
}





