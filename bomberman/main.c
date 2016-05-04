#include <SDL.h>
#include "game/game.h"

int main(void)
{

    SDL_Window *window;
    window = init_window(1024,512,"Bomberman");

    SDL_Renderer *renderer;
    renderer = init_renderer(window);

    Game game;
    Player * ply = &game.players[0];

    game.map = load_map("level2.map");
    load_walls(game.map, game.walls);
    *ply = create_player(1,1,0);

    game.player_count = 1;
    ply->bombs_count = 0;
    ply->bombs[0] = create_bomb(1,1,1,ply->id);
    ply->bombs[1] = create_bomb(1,1,1,ply->id);

    init_game(window, renderer, &game);

    return 0;
}