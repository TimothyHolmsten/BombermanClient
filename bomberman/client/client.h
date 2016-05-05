//
// Created by martin on 4/21/16.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H
#include <SDL.h>
#include <SDL_net.h>
#include "../game/game.h"
#include "../player/player.h"


void initClient(connection *con, Game *game);
void client_recv(connection *con, Game *game);
void client_send(connection *con, Game *game, char *msg);
#endif //CLIENT_CLIENT_H
