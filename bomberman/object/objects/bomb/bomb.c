//
// Created by Timothy Friberg Holmsten on 27/04/16.
//

#include "bomb.h"

Bomb create_bomb(int x, int y, int time, int owner) {

    Bomb bomb;

    bomb.x = x;
    bomb.y = y;
    bomb.time = time;
    bomb.owner = owner;

    return bomb;
}

