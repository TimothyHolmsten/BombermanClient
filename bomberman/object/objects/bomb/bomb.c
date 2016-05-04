//
// Created by Timothy Friberg Holmsten on 27/04/16.
//

#include "bomb.h"
#include "../../../game/game.h"

Bomb create_bomb(int x, int y, time_t tim, int owner) {

    Bomb bomb;
    time_t t;

    bomb.x = x;
    bomb.y = y;
    bomb.time = time(&t) + tim;
    bomb.owner = owner;

    return bomb;
}

void update_bombs(Bomb * bombs, Map * map) {

    time_t end_time;

    double diff;

    time(&end_time);

    for (int i = 0; i < GAME_MAX_BOMBS; i++) {
        diff = difftime(end_time, bombs[i].time);
        if (diff > 0) {
            bombs[i].placed = 0;
        }
    }
}



