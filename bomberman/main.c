#include <SDL.h>
#include "game/game.h"

int main(void)
{

    SDL_Window *window;
    window = init_window(640,480,"Bomberman");
    Game game;
    SDL_Renderer *renderer;
    renderer = init_renderer(window);
    game.player_count = 0;
    dlist_init(&game.players);
    int i = 1;

        SDL_SetWindowSize(window, 640, 480);
        //int temp = startMenu(window, renderer);
        SDL_SetWindowSize(window, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);

        init_game(window, renderer, &game);

    return 0;
}