//
// Created by martin on 5/20/16.
//

#ifndef CLIENT_MENU_H
#define CLIENT_MENU_H

#include "../image/image.h"
#include <SDL2/SDL.h>
#include <SDL_ttf.h>


SDL_Rect displayButton(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Texture *texture);

int checkButtons(SDL_Rect *buttons, int x, int y, int curMenu, int arrLength);

int mainMenu(SDL_Renderer *renderer, int *playerModel, char *playerName);

#endif //CLIENT_MENU_H
