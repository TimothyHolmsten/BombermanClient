//
// Created by martin on 5/20/16.
//

#ifndef CLIENT_MENU_H
#define CLIENT_MENU_H

#include "../image/image.h"
#include <SDL2/SDL.h>
#include <SDL_ttf.h>

//function to display any image where we want, and then free it when needed
SDL_Rect displayButton(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Texture *texture);

//function to display any text where we want, and then free it when needed
void displayText(SDL_Renderer *renderer, char *text,int x, int y, int w, int h, int fontSize );

//check if user pressed on any of the images ("buttons"), if so return that it was pressed
int checkButtons(SDL_Rect *buttons, int x, int y, int curMenu, int arrLength);

//check for keyboard input aswell as mouse
void get_key_input(char *name,SDL_Rect *menuButtons,SDL_Rect *buttons, int *menusSelect, int *charSelect);

//chooses between the diffrent menus
int mainMenu(SDL_Renderer *renderer, int *playerModel, char *playerName);

//render all image and text
int render_Main_Menu(SDL_Renderer *renderer);

//render all images and text for when 'Start' has been pressed, also checks for input
int render_Menu_Start(SDL_Renderer *renderer, char *name, int *charSelect, int *playerModel, char *playerName);

//render all images and text for when 'Start' has been pressed, also checks for input
int render_Menu_Options(SDL_Renderer *renderer);

int render_Menu_Help(SDL_Renderer *renderer);

#endif //CLIENT_MENU_H
