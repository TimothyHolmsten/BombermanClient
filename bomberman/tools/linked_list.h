//
// Created by martin on 4/28/16.
//

#ifndef CLIENT_LINKED_LIST_H
#define CLIENT_LINKED_LIST_H

#include <SDL.h>
#include <SDL_net.h>


typedef struct _DlistElement
{
    TCPsocket socket;
    Uint32   timeout; //In case someone dc's
    int id; //Unique ID for all players
    struct _DlistElement *next;
}DlistElement;


typedef struct _Dlist
{
    DlistElement* element;
}Dlist;

void dlist_init(Dlist *list);

DlistElement* dlist_createElement(int id, TCPsocket socket, Uint32 timeout);

void dlist_insert_first(Dlist* list, DlistElement* element);

void dlist_insert_last(Dlist* list, DlistElement* element);

void dlist_insert_middle(Dlist* list, DlistElement* element);

void dlist_removeAllElements(Dlist *list);

// remove element from list
int dlist_removeElement(Dlist *list, int number);

DlistElement *get_list_postition(Dlist *list, int id);

int dlist_size(Dlist *list);

void dlist_print(Dlist *list);



#endif

