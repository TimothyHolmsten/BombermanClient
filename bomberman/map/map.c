//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include <stdlib.h>
#include "map.h"

int load_map(char map[])
{
    int map_array[MAX_X][MAX_Y];

    char dest[100];
    // Loading map from right destination
    strcpy(dest, "bomberman/map/maps/");
    strcat(dest,map);

    FILE *fp;
    fp = fopen(dest, "r");

    char *array;
    size_t n = 0;
    int c;

    if (fp == NULL)
        return NULL; //could not open file

    array = malloc(1000);

    while ((c = fgetc(fp)) != EOF)
    {
        array[n++] = (char) c;
    }

    // don't forget to terminate with the null character
    array[n] = '\0';

    int x = 0;
    int y = 0;

    while(array[y] != '\0') {
        while (array[x] != '\n') {
            printf("%c", array[x]);
            //printf("X = %d\n", x);
            x++;
        }
        printf("\n");
        y = y + x;
        x=0;
    }

    return 0;
}
