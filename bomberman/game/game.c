//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "game.h"
#include "renderer/player/renderPlayer.h"
#include "renderer/object/renderObject.h"

// Arguments to be passed to new thread
struct args{
    Wall *walls;
    Player *players;
};

struct local_player_args{
    Map map;
    Player *player;
};

//multithreading to make update and render run on seperate threads
void* init_update(void* arg)
{
    struct args *arguments = (struct  args*) arg;
    while(1) {
        update_players(arguments->players);
        SDL_Delay(16); //Dont fry the CPU
    }
}

void* thread_update_player(void* arg) {

    struct local_player_args *arguments = (struct local_player_args*) arg;

    while(1) {
        update_local_player(arguments->player, arguments->map);
        update_bombs(arguments->player->bombs);
        SDL_Delay(16); //Dont fry the CPU
    }

}

int init_game(SDL_Window *window, SDL_Renderer *renderer, Game * game) {


    TCPsocket client;
    client = initClient();

    //Arguments for update thread
    struct args data;
    data.walls = game->walls;
    data.players = game->players;
    pthread_t t1, t2;

    pthread_create(&t1, NULL,init_update, &data );

    struct local_player_args local_p_data;
    local_p_data.map = game->map;
    local_p_data.player = &game->players[0];

    pthread_create(&t2, NULL, thread_update_player, &local_p_data);

    game_loop(window, renderer, game,client);
}


int game_loop(SDL_Window *window, SDL_Renderer *renderer, Game * game, TCPsocket client) {

    bool running = true;
    SDL_Event event;

    while (running)
    {
        //On exit pressed, exit
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        //render all element from bottom and up
        render_walls(window, game);
        render_bombs(window, game);
        render_players(window, game);

        //Show whats rendered
        SDL_RenderPresent(renderer);

        //Multiplayer
        client_DATA(client,game->players[0].x, game->players[0].y);

        //Spare the cpu, 16 =~ 60 fps
        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

SDL_Window * init_window(int w, int h, char *title) {

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            w,
            h,
            SDL_WINDOW_OPENGL);

    return window;
}

SDL_Renderer * init_renderer(SDL_Window *window) {

    SDL_Renderer *renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    return renderer;
}





