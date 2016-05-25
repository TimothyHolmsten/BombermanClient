//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "renderPlayer.h"

void render_players(SDL_Window *window, Game *game)
{
    SDL_Renderer *renderer = SDL_GetRenderer(window);

    char playerImage[20];
    SDL_Texture *texture;





    int ani;

    int i = 0;
    while(i < game->player_count) {

        //Render the specified texture for the player
        sprintf(playerImage, "%s%d%s", "Panda", get_list_postition(&game->players, i)->playerImage, ".png") ;
        texture = load_texture(renderer,playerImage);



        //This handles the selection of spritesheet  so it gets animated, renders from left to right, rotation selcts which column
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

