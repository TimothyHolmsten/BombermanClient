//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "game.h"


int game_loop(SDL_Window *window, SDL_Renderer *renderer, Wall walls[GAME_MAX_X*GAME_MAX_Y], Player players[]) {

    bool running = true;
    SDL_Event event;
    struct args{
        Wall *walls;
        Player *players;
    };

    void* test(void* arg)
    {

        struct args *arguments = (struct  args*) arg;
        while(1) {
            update_players(arguments->players, arguments->walls);
        }


    }
    struct args data;
    data.walls = walls;
    data.players = players;
    pthread_t thread_id;
    pthread_create(&thread_id, NULL,test, &data );
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





