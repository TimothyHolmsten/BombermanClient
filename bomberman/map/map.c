//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include <stdlib.h>
#include "map.h"

Map load_map(char map[])
{
    //int map_array[GAME_MAX_X][GAME_MAX_Y];
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

    //n = sizeof(a)/sizeof(a[0]);

    fclose(fp);

    return game_map;
}
