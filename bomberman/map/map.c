//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include <stdlib.h>
#include "map.h"

Map load_map(char map[])
{
    Map game_map;

    char dest[100];
    // Loading map from right destination
    strcpy(dest, "bomberman/map/maps/");
    strcat(dest,map);

    FILE *fp;
    fp = fopen(dest, "r");

    ssize_t read;

    if (fp == NULL)
        exit(EXIT_FAILURE);

    int x = 0;
    int y = 0;

    while ((read = getc(fp)) != EOF)
    {
        if (read != '\n')
        {
            //map_array[x++][y] = ((int) read) - 48;
            game_map.map_array[x++][y] = ((int) read) - 48;
        }
        else
        {
            x = 0;

            y++;
        }
    }

    fclose(fp);

    return game_map;
}

int get_object_from_position(Map map, int x, int y)
{
    return map.map_array[x][y];
}

void set_object_from_position(Map * map, int x, int y, int new_object)
{
    map->map_array[x][y] = new_object;
}

int get_objects_count(Map map, char * object_type)
{
    int walls = 0;

    int i = 0;

    for (int y = 0; y < GAME_MAX_Y; y++)
    {
        for(int x = 0; x < GAME_MAX_X; x++)
        {
            if (map.map_array[x][y] == 1)
                walls++;
            i++;
        }
    }

    if (strcmp(object_type, "Walls") == 0)
        return walls;

    return -1;

}

int map_is_blocked(Map * map, int x, int y) {

    if (map->map_array[x][y] == 1)
        return 1;
    if (map->map_array[x][y] == 3)
        return 1;

    return 0;
}
