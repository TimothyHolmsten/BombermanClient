//
// Created by Timothy Friberg Holmsten on 26/04/16.
//

#include "image.h"

SDL_Texture * load_texture(SDL_Renderer *renderer, char path[])
{
    char dest[100];
    strcpy(dest,"bomberman/image/images/");
    strcat(dest, path);

    SDL_Texture * texture;
    texture = IMG_LoadTexture(renderer, dest);

    if(texture == NULL){
        printf("%s", SDL_GetError());
    }

    return texture;
}