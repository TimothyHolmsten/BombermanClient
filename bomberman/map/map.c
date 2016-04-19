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

int map_is_blocked(Map map, int x, int y) {

    if (map.map_array[x][y] == 1)
        return 1;

    return 0;
}
