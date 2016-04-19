//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#ifndef CLIENT_MAP_H
#define CLIENT_MAP_H

#include <stdio.h>
#include <string.h>

#define MAX_X 16
#define MAX_Y 16

typedef struct map{
    int map_array[MAX_X][MAX_Y];
} Map;


Map load_map(char map[]);

#endif //CLIENT_MAP_H
