//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "renderPlayer.h"

void render_players(SDL_Window *window, Game *game)
{
    SDL_Renderer *renderer = SDL_GetRenderer(window);

    SDL_Texture *texture = load_texture(renderer,"plejer.png");

    int i = 0;
    while(i < game->player_count) {
        if(get_list_postition(&game->players, i)->alive == 1) {
            SDL_Rect rect = {(GAME_WINDOW_WIDTH / 2) / 2 + (int) get_list_postition(&game->players, i)->anix,
                             (int) get_list_postition(&game->players, i)->aniY, 32, 32};
            SDL_RenderCopy(renderer, texture, NULL, &rect);

        }
        i++;
    }
    SDL_DestroyTexture(texture);
}

