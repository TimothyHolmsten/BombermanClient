//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "renderObject.h"

void render_explosion(SDL_Window *window, Game * game)
{
    SDL_Renderer *renderer = SDL_GetRenderer(window);

    SDL_Texture * texture;
    texture = load_texture(renderer, "Explosion.png");

    for (int y = 0; y < GAME_MAX_Y; y++)
    {
        for (int x = 0; x < GAME_MAX_X; x++) {
            if (get_object_from_position(game->map, x, y) == 9) {
                SDL_Rect rect = {(GAME_WINDOW_WIDTH / 2) / 2 + x * 32, y * 32, 32, 32};
                SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
            }
        }
    }
    SDL_DestroyTexture(texture);
}

void render_grass(SDL_Window *window)
{
    SDL_Renderer *renderer = SDL_GetRenderer(window);

    SDL_Texture *texture;
    texture = load_texture(renderer, "Grass.png");

    for (int y = 0; y < GAME_MAX_Y; y++)
    {
        for (int x = 0; x < GAME_MAX_X; x++) {
            SDL_Rect rect = {(GAME_WINDOW_WIDTH / 2) / 2 + x * 32, y * 32, 32, 32};
            SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
        }
    }
    SDL_DestroyTexture(texture);
}

void render_boxes(SDL_Window *window, Game * game)
{
    SDL_Renderer *renderer = SDL_GetRenderer(window);

    SDL_Texture *texture;
    texture = load_texture(renderer, "box.png");

    for (int y = 0; y < GAME_MAX_Y; y++)
    {
        for (int x = 0; x < GAME_MAX_X; x++) {
            if (get_object_from_position(game->map, x, y) == DESTRUCTABLE_WALL)
            {
                SDL_Rect rect = {(GAME_WINDOW_WIDTH / 2) / 2 + x * 32, y * 32, 32, 32};
                SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
            }
        }
    }
    SDL_DestroyTexture(texture);
}

void render_walls(SDL_Window *window, Game * game) {

    SDL_Renderer *renderer = SDL_GetRenderer(window);

    SDL_Texture *texture;
    texture = load_texture(renderer, "Wall.png");

    for (int y = 0; y < GAME_MAX_Y; y++)
    {
        for (int x = 0; x < GAME_MAX_X; x++) {
            if (get_object_from_position(game->map, x, y) == WALL)
            {
                SDL_Rect rect = {(GAME_WINDOW_WIDTH / 2) / 2 + x * 32, y * 32, 32, 32};
                SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
            }
        }
    }
    SDL_DestroyTexture(texture);
}

void render_bombs(SDL_Window *window, Game *game) {
    int i = 0;
    SDL_Renderer *renderer = SDL_GetRenderer(window);

    SDL_Texture *texture;
    texture = load_texture(renderer, "Bomb.png");
    if(game->player_count != 0) {
        for (int pl_count = 0; pl_count < game->player_count; pl_count++) {
                if (get_list_postition(&game->players, pl_count)->bombs[i].placed != 0) {
                    SDL_Rect rect = {
                            (GAME_WINDOW_WIDTH / 2) / 2 + get_list_postition(&game->players, pl_count)->bombs[i].x * 32,
                            get_list_postition(&game->players, pl_count)->bombs[i].y * 32,
                            32,
                            32
                    };

                    SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
                }
        }
    }
    SDL_DestroyTexture(texture);
};