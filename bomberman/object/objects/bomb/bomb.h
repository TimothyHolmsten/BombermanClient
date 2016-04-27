//
// Created by Timothy Friberg Holmsten on 27/04/16.
//

#ifndef CLIENT_BOMB_H
#define CLIENT_BOMB_H

#include <time.h>

typedef struct Bomb {
    int x;
    int y;
    time_t time; // until explosion
    int owner; // player id
    int placed;
}Bomb;

Bomb create_bomb(int x, int y, time_t time, int owner);
void update_bombs(Bomb * bombs);

#endif //CLIENT_BOMB_H
