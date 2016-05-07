//
// Created by martin on 4/21/16.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H
#include <SDL.h>
#include <SDL_net.h>
#include "../main.h"
#include "../player/player.h"


void initClient(Game *game);
void client_recv( Game *game);
void client_send(Game *game, char *msg);
#endif //CLIENT_CLIENT_H
