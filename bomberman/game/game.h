//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H

#include <stdbool.h>
#include <SDL.h>

SDL_Window * init_window(int w, int h, char *title);
SDL_Renderer * init_renderer(SDL_Window *window);
int game_loop(SDL_Window *window, SDL_Renderer *renderer);

#endif //CLIENT_GAME_H
