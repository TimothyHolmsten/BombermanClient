//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#ifndef CLIENT_RENDERPLAYER_H
#define CLIENT_RENDERPLAYER_H


#include "../../../player/player.h"
#include "../../../map/map.h"
#include <SDL.h>
void render_players(SDL_Renderer *renderer, Player players[]);

void  update_players(Player players[]);

#endif //CLIENT_RENDERPLAYER_H

