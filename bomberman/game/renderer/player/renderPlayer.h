//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

/**
 * Hello
 */

#ifndef CLIENT_RENDERPLAYER_H
#define CLIENT_RENDERPLAYER_H


#include "../../../player/player.h"
#include "../../../object/objects/wall/wall.h"
#include "../../../map/map.h"
#include <SDL.h>
#include "stdbool.h"
#include <math.h>
void render_players(SDL_Window * window, Player players[]);

#endif //CLIENT_RENDERPLAYER_H

