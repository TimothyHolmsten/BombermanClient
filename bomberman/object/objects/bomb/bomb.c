//
// Created by Timothy Friberg Holmsten on 27/04/16.
//

#include "bomb.h"
#include "../../../game/game.h"

Bomb create_bomb(int x, int y, time_t tim, int owner, int radius) {

    Bomb bomb;
    time_t t;
    bomb.x = x;
    bomb.y = y;
    bomb.time = time(&t) + tim;
    bomb.owner = owner;
    bomb.radius = radius;

    return bomb;
}

void bomb_explode(Bomb * bomb, Map * map)
{
    int i = 0;
    int object = EXPLOSION;

    while (i < 2) {

        if (i != 0)
            object = 0;

        // Exploding X
        for (int x = 0; x < bomb->radius; x++) {
            if (get_object_from_position(*map, bomb->x + x, bomb->y) == WALL || bomb->x + x == GAME_MAX_X)
                break;
            set_object_from_position(map, bomb->x + x, bomb->y, object);
        }
        for (int x = 0; x > -bomb->radius; x--) {
            if (get_object_from_position(*map, bomb->x + x, bomb->y) == WALL || bomb->x + x == 0)
                break;
            set_object_from_position(map, bomb->x + x, bomb->y, object);
        }

        // Exploding Y
        for (int y = 0; y < bomb->radius; y++) {
            if (get_object_from_position(*map, bomb->x, bomb->y + y) == WALL || bomb->y + y == GAME_MAX_Y)
                break;
            set_object_from_position(map, bomb->x, bomb->y + y, object);
        }
        for (int y = 0; y > -bomb->radius; y--) {
            if (get_object_from_position(*map, bomb->x, bomb->y + y) == WALL || bomb->y + y == 0)
                break;
                set_object_from_position(map, bomb->x, bomb->y + y, object);
        }
        if (i == 0)
            SDL_Delay(100);
        i++;
    }
}

void update_bombs(Bomb * bombs, Map * map) {

    time_t end_time;

    double diff = 0;

    time(&end_time);

    for (int i = 0; i < GAME_MAX_BOMBS; i++) {
        diff = difftime(end_time, bombs[i].time);
        if (diff > 0) {
            if (bombs[i].placed == 1)
                bomb_explode(&bombs[i], map);
            bombs[i].x = 0;
            bombs[i].y = 0;
            bombs[i].placed = 0;
        }
    }
}



