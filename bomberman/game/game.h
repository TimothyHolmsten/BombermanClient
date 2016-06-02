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
#include "../main.h"
#include "../menu/menu.h"

#define GAME_MAX_BOMBS 1
#define GAME_WINDOW_WIDTH 1024
#define GAME_WINDOW_HEIGHT 480

SDL_Window * init_window(int w, int h, char *title);
SDL_Renderer * init_renderer(SDL_Window *window);
int game_loop(SDL_Window *window, SDL_Renderer *renderer, Game * game);
int init_game(SDL_Window *window, SDL_Renderer *renderer, Game * game);
void checkWin(Game *game, SDL_Renderer *renderer, int *lost, int *running);
#endif //CLIENT_GAME_H

