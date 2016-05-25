//
// Created by martin on 4/28/16.
//

#ifndef CLIENT_LINKED_LIST_H
#define CLIENT_LINKED_LIST_H

#include <SDL.h>
#include <SDL_net.h>
#include "../object/objects/bomb/bomb.h"

//TODO
//Should move this struct to a place that makes more sense
//Low priority since it works fine as it is, and we don't use
//the linked list for something else.
typedef struct _DlistElement
{
    int x;
    int y;

    int rotation;
    int animation_timer;
    int moving;
    int animation;
    int playerImage;
    float anix;
    float aniY;

    int alive;
    int id;
    int local;

    int bomb_radius;
    Bomb bombs[8];
    int bombs_count;
    struct  _DlistElement *next;
}DlistElement;


typedef struct PlayerList
{
    DlistElement * element;
}Dlist;

void dlist_init(Dlist *list);

DlistElement* dlist_createElement(int id, int x, int y, int playerImage);

void dlist_insert_first(Dlist* list, DlistElement* element);

void dlist_insert_last(Dlist* list, DlistElement* element);

void dlist_insert_middle(Dlist* list, DlistElement* element);

void dlist_removeAllElements(Dlist *list);

// remove element from list
int dlist_removeElement(Dlist *list, int number);

DlistElement *get_list_postition(Dlist *list, int pos);

int get_pos_from_id(Dlist *list, int id);

int dlist_size(Dlist *list);

void dlist_print(Dlist *list);



#endif

