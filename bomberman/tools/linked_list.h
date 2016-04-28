//
// Created by martin on 4/28/16.
//

#ifndef CLIENT_LINKED_LIST_H
#define CLIENT_LINKED_LIST_H

#include "../tempServer.h"
#include <SDL.h>
#include <SDL_net.h>

typedef struct data{
    TCPsocket socket;
    Uint32   timeout; //In case someone dc's
    int id; //Unique ID for all players
    struct data *next;
}Data;


void add_front(Data** head,TCPsocket socket, Uint32 timeout, int id);
Data * get_list_postition(Data** head, int postion);
void remove_link(Data** head, int value_to_remove);
int list_size(Data* head);
void display_list(Data* head);

void initLinkedList();

#endif //CLIENT_LINKED_LIST_H
