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

/*TODO
 * Fix a better way to iterate walls
 * */

void load_walls(Map map, Wall walls[])
{
    int i = 0;

    for (int y = 0; y < GAME_MAX_Y; y++)
    {
        for(int x = 0; x < GAME_MAX_X; x++)
        {
            if (map.map_array[x][y] == 1)
            {
                walls[i] = create_wall(x,y);
            }
            else
            {
                // Really ugly
                //walls[i] = create_wall(10000,10000);
            }
            i++;
        }
    }
}
