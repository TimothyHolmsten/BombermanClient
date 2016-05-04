#include <SDL.h>
#include "game/game.h"

int main(void)
{

    SDL_Window *window;
    window = init_window(1024,512,"Bomberman");

    SDL_Renderer *renderer;
    renderer = init_renderer(window);

    Game game;

    dlist_init(&game.players);

    game.map = load_map("level1.map");
    load_walls(game.map, game.walls);
    create_player(&game.players,1,1,0);

    dlist_print(&game.players);
    game.player_count = 1;


    init_game(window, renderer, &game);

    return 0;
}