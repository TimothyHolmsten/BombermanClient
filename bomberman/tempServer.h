//
// Created by martin on 4/21/16.
//

#ifndef CLIENT_TEMPSERVER_H
#define CLIENT_TEMPSERVER_H
#include <SDL.h>
#include <SDL_net.h>
#include <stdbool.h>
#include <stdio.h>
#include "tools/linked_list.h"

#define MAX_PLAYER 8

void init_server();
void add_clients(TCPsocket tmpsocket, SDLNet_SocketSet *sockets,Dlist *socketList, int *playernum, int *curID, char *tmp);
void check_data(TCPsocket tmpsocket, SDLNet_SocketSet *sockets,Dlist *socketList, int *playernum, int *curID, char *tmp);

#endif //CLIENT_TEMPSERVER_H

