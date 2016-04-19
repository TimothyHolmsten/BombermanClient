//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "map.h"

int load_map(char map[])
{
    char dest[100];
    // Loading map from right destination
    strcpy(dest, "bomberman/map/maps/");
    strcat(dest,map);

    FILE *fp;
    fp = fopen(dest, "r");

    if(fp)
    {
        printf("Found file");
    }

    fclose(fp);

    return 0;
}
