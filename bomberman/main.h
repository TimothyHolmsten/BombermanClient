//
// Created by martin on 5/7/16.
//

#ifndef CLIENT_MAIN_H
#define CLIENT_MAIN_H
#include <pthread.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_net.h>
#include "tools/linked_list.h"
#include "map/map.h"
#include "object/objects/wall/wall.h"

typedef struct game {
    Dlist players;
    Wall walls[GAME_MAX_X*GAME_MAX_Y];
    Map map;
    int player_count;
    TCPsocket client;
    SDLNet_SocketSet server;
    int gameRunning;
    int gameClosed;
}Game;

#endif //CLIENT_MAIN_H
