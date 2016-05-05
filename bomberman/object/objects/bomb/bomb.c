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

void bomb_explode(Bomb * bomb, Map * map)
{

    // Exploding X
    for(int x = 0; x < 5; x++)
    {
        if (get_object_from_position(*map, bomb->x + x, bomb->y) == 1 || bomb->x + x == GAME_MAX_X)
            break;
        set_object_from_position(map, bomb->x + x, bomb->y, 0);
    }
    for(int x = 0; x > -5; x--)
    {
        if (get_object_from_position(*map, bomb->x + x, bomb->y) == 1 || bomb->x + x == 0)
            break;
        set_object_from_position(map, bomb->x + x, bomb->y, 0);
    }

    // Exploding Y
    for(int y = 0; y < 5; y++)
    {
        if (get_object_from_position(*map, bomb->x, bomb->y + y) == 1 || bomb->y + y == GAME_MAX_Y)
            break;
        set_object_from_position(map, bomb->x, bomb->y + y, 0);
    }
    for(int y = 0; y > -5; y--)
    {
        if (get_object_from_position(*map, bomb->x, bomb->y + y) == 1 || bomb->y + y == 0)
            break;
        set_object_from_position(map, bomb->x, bomb->y + y, 0);
    }
}

void update_bombs(Bomb * bombs, Map * map) {

    time_t end_time;

    double diff;

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



