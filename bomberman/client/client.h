//
// Created by martin on 4/21/16.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H
#include <SDL.h>
#include <SDL_net.h>

TCPsocket initClient();
void client_DATA(TCPsocket client, int playerX, int playerY);
#endif //CLIENT_CLIENT_H
