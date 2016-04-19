//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "map.h"

int load_map(char *map)
{
    FILE *fp;
    fp = fopen(map, "r");

    char ch = getc(fp);

    int count = 0;

    while (ch != '\n')
    {
        printf("%c", ch);
    }

    return 0;
}
