//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H

#include <pthread.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_net.h>
#include "../player/player.h"
#include "../map/map.h"
#include "../object/objects/wall/wall.h"


#define GAME_MAX_BOMBS 2

typedef struct Connection{
    TCPsocket client;
    TCPsocket client2;
    SDLNet_SocketSet server;
}connection;

typedef struct Game {
    Player players[8];
    Wall walls[GAME_MAX_X*GAME_MAX_Y];
    Map map;
    int player_count;
}Game;

SDL_Window * init_window(int w, int h, char *title);
SDL_Renderer * init_renderer(SDL_Window *window);
int game_loop(SDL_Window *window, SDL_Renderer *renderer, Game * game, connection *con);
int init_game(SDL_Window *window, SDL_Renderer *renderer, Game * game);

#endif //CLIENT_GAME_H

