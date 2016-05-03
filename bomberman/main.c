#include <stdio.h>
#include <SDL.h>
#include "game/game.h"
#include "map/map.h"
#include "object/objects/wall/wall.h"
#include "player/player.h"
#include "client/client.h"
#include <pthread.h>
#include "map/map.h"
#include "tools/linked_list.h"

int main(void)
{

    SDL_Window *window;
    window = init_window(1024,512,"Bomberman");

    SDL_Renderer *renderer;
    renderer = init_renderer(window);

    Game game;

    game.map = load_map("level2.map");
    load_walls(game.map, game.walls);
    game.players[0] = create_player(1,1,0);
    game.players[1] = create_player(3,1,1);
    game.player_count = 2;
    game.players[0].bombs_count = 0;

   //printf("%d", get_objects_count(game.map, "Walls"));


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


    init_game(window, renderer, &game);



    return 0;
}