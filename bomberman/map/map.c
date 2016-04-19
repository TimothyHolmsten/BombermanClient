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

    char *ch;

    int count;
    if (fp) {
        while ((count = getc(fp)) != EOF)
        {
            putchar(count);
        }
        fclose(fp);
    }
    else{printf("error cant find file");}
    return 0;
}
