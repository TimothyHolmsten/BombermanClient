//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#ifndef CLIENT_WALL_H
#define CLIENT_WALL_H

#include "../../../map/map.h"

typedef struct wall{
    int x;
    int y;
}Wall;

/* Creates a wall from the Wall struct and returns it */
Wall create_wall(int x, int y);

void load_walls(Map map, Wall walls[]);

#endif //CLIENT_WALL_H
