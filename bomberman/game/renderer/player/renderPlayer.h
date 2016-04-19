//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#ifndef CLIENT_RENDERPLAYER_H
#define CLIENT_RENDERPLAYER_H

#include <SDL_render.h>
#include "../../../player/player.h"
#include "../../../map/map.h"

void render_players(SDL_Renderer *renderer, Player players[]);

#endif //CLIENT_RENDERPLAYER_H

