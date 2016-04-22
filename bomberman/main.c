#include <stdio.h>
#include <SDL.h>
#include "game/game.h"
#include "map/map.h"
#include "object/objects/wall/wall.h"
#include "player/player.h"



int main(void)
{
    SDL_Window *window;
    window = init_window(1024,512,"Bomberman");

    SDL_Renderer *renderer;
    renderer = init_renderer(window);

    Wall walls[GAME_MAX_X*GAME_MAX_Y];

    Map _map;

    _map = load_map("level1.map");

    load_walls(_map, walls);

    Player ply1 = create_player(1.0,1.0,0);
    Player ply2 = create_player(4.0,1.0,0);
    //Player *players[] = {ply1};

    Player players[8];
    players[0] = ply1;
    players[1] = ply2;


    /* GOOD STUFF
    for (int i = 0; i < GAME_MAX_Y; i++)
    {
        for(int j = 0; j < GAME_MAX_X; j++)
        {
            printf("%d",_map.map_array[j][i]);
        }
        printf("\n");
    }
    */


    init_game(window, renderer, walls, players, _map);

    return 0;
}