//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#ifndef CLIENT_RENDEROBJECT_H
#define CLIENT_RENDEROBJECT_H

#include <SDL_render.h>
#include "../../../object/objects/wall/wall.h"
#include <SDL_image.h>

void render_walls(SDL_Window *window, Wall * walls);

#endif //CLIENT_RENDEROBJECT_H
