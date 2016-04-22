//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "game.h"

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
    }
}

void* thread_update_player(void* arg) {

    struct local_player_args *arguments = (struct local_player_args*) arg;

    while(1) {
        update_local_player(arguments->player, arguments->map);
    }

}

int init_game(SDL_Window *window, SDL_Renderer *renderer, Wall walls[GAME_MAX_X * GAME_MAX_Y], Player players[], Map map) {

    struct args data;
    data.walls = walls;
    data.players = players;
    pthread_t t1, t2;

    pthread_create(&t1, NULL,init_update, &data );

    struct local_player_args local_p_data;
    local_p_data.map = map;
    local_p_data.player = &players[0];

    pthread_create(&t2, NULL, thread_update_player, &local_p_data);

    game_loop(window, renderer, walls, players);

    return 0;
}


int game_loop(SDL_Window *window, SDL_Renderer *renderer, Wall walls[GAME_MAX_X*GAME_MAX_Y], Player players[]) {

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        render_walls(renderer, walls);
        render_players(renderer, players);


        SDL_RenderPresent(renderer);

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





