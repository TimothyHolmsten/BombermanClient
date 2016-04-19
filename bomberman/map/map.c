//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include <stdlib.h>
#include "map.h"

int load_map(char map[])
{
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
        code[n++] = (char) c;
        if (c == '1')
        {
            printf("Wall\n");
        }

        if (c == '0')
        {
            printf("floor\n");
        }
    }

    // don't forget to terminate with the null character
    code[n] = '\0';

    return 0;
}
