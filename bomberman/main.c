#include <SDL.h>
#include "game/game.h"
#include "menu/menu.h"

int main(void)
{

    SDL_Window *window;
    window = init_window(640,480,"Bomberman");
    Game game;
    SDL_Renderer *renderer;
    renderer = init_renderer(window);

    int  playerModel=0;
    char playerName[20];

    int running = 1;

    while(running == 1){

        //Set the variables needed to run the game to default
        game.player_count = 0;
        game.gameRunning = 0;
        game.gameClosed = 0;
        dlist_init(&game.players);

        SDL_SetWindowSize(window, 640, 480);
        mainMenu(renderer, &playerModel,playerName); //Start menu, also get character and name
                                                     // we currently don't use name but if you want it we have done the ground work
        game.localPlayerChar =playerModel;

        running = init_game(window, renderer, &game);


    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}