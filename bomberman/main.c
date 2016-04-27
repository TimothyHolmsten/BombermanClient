#include <stdio.h>
#include <SDL.h>
#include "game/game.h"
#include "map/map.h"
#include "object/objects/wall/wall.h"
#include "player/player.h"
#include "tempServer.h"
#include "client/client.h"
#include <pthread.h>

void* start_server(void* arg) {

    initServer();
}

int main(void)
{
    SDL_Window *window;
    window = init_window(1024,512,"Bomberman");

    SDL_Renderer *renderer;
    renderer = init_renderer(window);

    pthread_t t3;
    pthread_create(&t3, NULL,start_server, NULL );
    SDL_Delay(500); //While server is local make sure it starts before client

    Game game;

    game.map = load_map("level1.map");
    load_walls(game.map, game.walls);
    game.players[0] = create_player(1,1,0);



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