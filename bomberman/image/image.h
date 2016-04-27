//
// Created by Timothy Friberg Holmsten on 26/04/16.
//

#ifndef CLIENT_IMAGE_H
#define CLIENT_IMAGE_H

#include <string.h>
#include <SDL_image.h>

SDL_Texture * load_texture(SDL_Renderer *renderer, char path[]);

#endif //CLIENT_IMAGE_H
