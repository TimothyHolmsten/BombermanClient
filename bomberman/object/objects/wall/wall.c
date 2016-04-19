//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "wall.h"

Wall create_wall(int x, int y)
{
    Wall wall;
    wall.x = x;
    wall.y = y;

    return wall;
}

Wall * load_walls(Map map)
{
    Wall wall;
    Wall walls[GAME_MAX_X*GAME_MAX_Y];

    int i = 0;

    for (int y = 0; y < GAME_MAX_Y; y++)
    {
        for(int x = 0; x < GAME_MAX_X; x++)
        {
            if (map.map_array[x][y] == 1)
            {
                walls[i].x = x;
                walls[i].y = y;
                i++;
            }
        }
        i = 0;
    }
    printf("%d ", walls[17].x);
    return walls;
}
