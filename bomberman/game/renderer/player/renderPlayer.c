//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "renderPlayer.h"

void render_players(SDL_Window *window, Game *game)
{
    SDL_Renderer *renderer = SDL_GetRenderer(window);

    SDL_Texture *texture = load_texture(renderer,"Panda.png");


    int ani;

    int i = 0;
    while(i < game->player_count) {

        //This handles the selection of spritesheet so it gets animated
        if(get_list_postition(&game->players, i)->moving == 1) {
            if (get_list_postition(&game->players, i)->animation_timer == 3) {
                get_list_postition(&game->players, i)->animation += 1;
                if (get_list_postition(&game->players, i)->animation > 2) {
                    get_list_postition(&game->players, i)->animation = 0;
                }
                get_list_postition(&game->players, i)->animation_timer = 0;
            }
            ani =  get_list_postition(&game->players, i)->animation;
            get_list_postition(&game->players, i)->animation_timer += 1;
        }
        else{
            ani = 0;
        }

        if(get_list_postition(&game->players, i)->alive == 1) {
            SDL_Rect rect = {(GAME_WINDOW_WIDTH / 2) / 2 + (int) get_list_postition(&game->players, i)->anix,
                             (int) get_list_postition(&game->players, i)->aniY, 32, 32};
            SDL_Rect ply = {32*ani, 32*get_list_postition(&game->players, i)->rotation, 32, 32};
            SDL_RenderCopy(renderer, texture, &ply, &rect);

        }
        i++;
    }
    SDL_DestroyTexture(texture);
}

