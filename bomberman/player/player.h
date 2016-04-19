//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H

typedef struct Player{
    int x;
    int y;
    int id;
} Player;

Player create_player(int x, int y, int id);

#endif //CLIENT_PLAYER_H
