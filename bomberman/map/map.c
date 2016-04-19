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

    char *code;
    size_t n = 0;
    int c;

    if (fp == NULL)
        return NULL; //could not open file

    code = malloc(1000);

    while ((c = fgetc(fp)) != EOF)
    {
        while (c != '\n')
        {
            printf("%c", c);
        }
        code[n++] = (char) c;
    }

    // don't forget to terminate with the null character
    code[n] = '\0';

    return 0;
}
