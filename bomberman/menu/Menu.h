//
// Created by martin on 5/17/16.
//

#ifndef CLIENT_MENU_H
#define CLIENT_MENU_H
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>

int startMenu(SDL_Window* window,SDL_Renderer* renderer);
void show_menu(SDL_Renderer *renderer, SDL_Texture* texture, SDL_Surface * surface, SDL_Rect* menu, SDL_Rect* fullWindow, TTF_Font* font, SDL_Surface* message, SDL_Texture* text, SDL_Color textColor, SDL_Rect header);
int initMenu(SDL_Window* window,SDL_Renderer* renderer);
#endif //CLIENT_MENU_H
