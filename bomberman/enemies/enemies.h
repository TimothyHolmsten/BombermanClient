//
// Created by martin on 5/1/16.
//

#ifndef CLIENT_ENEMIES_H
#define CLIENT_ENEMIES_H

typedef struct Enemy{
    int x;
    int y;
    int id;
    Bomb bombs[2];
    int bombs_count;
} enemy;

void show_enemy();
#endif //CLIENT_ENEMIES_H
