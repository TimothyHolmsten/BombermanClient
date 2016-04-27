//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#ifndef CLIENT_MAP_H
#define CLIENT_MAP_H

#include <stdio.h>
#include <string.h>
#include <monetary.h>
#define GAME_MAX_X 15
#define GAME_MAX_Y 15

typedef struct map{
    int map_array[GAME_MAX_X][GAME_MAX_Y];
} Map;

Map load_map(char map[]);

int map_is_blocked(Map map, int x, int y);
int get_objects_count(Map map, char * object_type);

#endif //CLIENT_MAP_H
