//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "player.h"

Player create_player(float x, float y, int id)
{
    Player ply;
    ply.x = x;
    ply.y = y;
    ply.id = id;

    return ply;
}