//
// Created by Timothy Friberg Holmsten on 27/04/16.
//

#ifndef CLIENT_BOMB_H
#define CLIENT_BOMB_H

typedef struct Bomb {
    int x;
    int y;
    int time; // until explosion
    int owner; // player id
}Bomb;

Bomb create_bomb(int x, int y, int time, int owner);

#endif //CLIENT_BOMB_H
