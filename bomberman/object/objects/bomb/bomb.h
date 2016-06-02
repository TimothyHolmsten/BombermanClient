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

/* Creates a bomb from the Bomb struct and returns it */
Bomb create_bomb(int x, int y, time_t time, int owner, int radius);
/* Looping a "cross" and checks if there are walls, players or boxes */
void bomb_explode(Bomb * bomb, Map * map);
/* Used by a thread function to update all the bombs in the game
 * Checks if the bombs should explode or not
 * */
void update_bombs(Bomb * bombs, Map * map);

#endif //CLIENT_BOMB_H
