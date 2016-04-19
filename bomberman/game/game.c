//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "game.h"


int game_loop(SDL_Window *window, SDL_Renderer *renderer) {

    bool running = true;
    SDL_Event event;

    while (running)
    {
        if(event.type == SDL_QUIT)
        {
            running = false;
        }
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





