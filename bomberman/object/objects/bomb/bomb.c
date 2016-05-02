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
<<<<<<< Updated upstream
        if (diff > 0) {
            bombs[i].x = 13+bombs[i].order;
            bombs[i].y = 14;
=======
        if (diff > 0 && bombs[i].placed != 0) {

            //Bomb bomb = bombs[i];

            //set_object_from_position(&bombs[i].map, 1, 1, 1);
            //set_object_from_position(&bombs[i].map, 2, 1, 1);
            //map->map_array[1][1] = 1;
            set_object_from_position(map,1,1,1);

            bombs[i].x = 10;
            bombs[i].y = 10;
>>>>>>> Stashed changes
            bombs[i].placed = 0;
        }
    }
}



