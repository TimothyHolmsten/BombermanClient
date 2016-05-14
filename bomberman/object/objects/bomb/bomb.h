//
// Created by Timothy Friberg Holmsten on 27/04/16.
//

#ifndef CLIENT_BOMB_H
#define CLIENT_BOMB_H

#include <time.h>
#include "../../../map/map.h"

typedef struct Bomb {
    int x;
    int y;
    time_t time; // until explosion
    int owner; // player id
    int placed;
    int radius;
}Bomb;

Bomb create_bomb(int x, int y, time_t time, int owner, int radius);
void bomb_explode(Bomb * bomb, Map * map);
void update_bombs(Bomb * bombs, Map * map);

#endif //CLIENT_BOMB_H
