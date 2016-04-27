//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H

#include <pthread.h>
#include <stdbool.h>
#include <SDL.h>
#include "renderer/object/renderObject.h"
#include "../player/player.h"
#include "renderer/player/renderPlayer.h"
#include "../client/client.h"

typedef struct Game {
    Player players[8];
    Wall walls[GAME_MAX_X*GAME_MAX_Y];
    Map map;
}Game;

SDL_Window * init_window(int w, int h, char *title);
SDL_Renderer * init_renderer(SDL_Window *window);
int game_loop(SDL_Window *window, SDL_Renderer *renderer, Game * game, TCPsocket client);
int init_game(SDL_Window *window, SDL_Renderer *renderer, Game * game);

#endif //CLIENT_GAME_H

