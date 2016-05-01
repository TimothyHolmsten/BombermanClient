//
// Created by martin on 4/21/16.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H
#include <SDL.h>
#include <SDL_net.h>
#include "../game/game.h"


void initClient(connection *con);
void client_DATA(connection *con, Game *game);
#endif //CLIENT_CLIENT_H
