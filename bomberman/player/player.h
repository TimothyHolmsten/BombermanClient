//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H

typedef struct Player{
    float x;
    float y;
    int id;
} Player;

Player create_player(float x, float y, int id);

void update_players(Player players[]);

#endif //CLIENT_PLAYER_H