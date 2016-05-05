//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include "game.h"
#include "renderer/player/renderPlayer.h"
#include "renderer/object/renderObject.h"
#include "../client/client.h"

// Arguments to be passed to new thread
struct args{
    Wall *walls;
    Dlist *players;
};

struct local_player_args{
    Map * map;
    DlistElement *player;
};

//multithreading to make update and render run on seperate threads
void * init_update(void* arg)
{
    struct args *arguments = (struct  args*) arg;
    if(arguments->players != NULL) {
        while (1) {
            update_players(arguments->players);
            SDL_Delay(16); //Dont fry the CPU
        }
    }
}

void * thread_update_player(void * arg) {

    struct local_player_args *arguments = (struct local_player_args*) arg;

        while (1) {

                update_local_player(arguments->player, arguments->map);
                //update_bombs(arguments->player->bombs, arguments->map); casues memory problem
                SDL_Delay(16); //Dont fry the CPU
    }
}

int init_game(SDL_Window *window, SDL_Renderer *renderer, Game * game) {

    connection con;
    //initClient(&con, game);
    SDL_Delay(500);
    //client_recv(&con, game);
    //Arguments for update thread
    struct args data;
    data.walls = game->walls;
    data.players = &game->players;
    pthread_t t1, t2;

    pthread_create(&t1, NULL,init_update, &data );

    struct local_player_args local_p_data;
    local_p_data.map = &game->map;
    local_p_data.player = get_list_postition(&game->players, 0);

    pthread_create(&t2, NULL, thread_update_player, &local_p_data);

    //set_object_from_position(&game->map,1,1,1);

    game_loop(window, renderer, game,&con);

    return 0;
}


int game_loop(SDL_Window *window, SDL_Renderer *renderer, Game * game, struct Connection *con) {

    bool running = true;
    SDL_Event event;

    while (running)
    {
        //On exit pressed, exit
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                char msg[100]; // Send this to connected device
                sprintf(msg, "3 %d\n", get_list_postition(&game->players, 0)->id);
                client_send(con, game, &msg);
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        //render all element from bottom and up
        if(get_list_postition(&game->players, 0) != NULL) {
            render_grass(window, game);
            render_walls(window, game);
            render_boxes(window, game);
            render_bombs(window, game);
            render_players(window, game);

        }

        //Show whats rendered
        SDL_RenderPresent(renderer);

        //Multiplayer
       // client_recv(con, game);
        if(get_list_postition(&game->players, 0) != NULL) {
            char msg[100]; // Send this to connected device
            sprintf(msg, "2 %d %d %d \n", get_list_postition(&game->players, 0)->id,
                    get_list_postition(&game->players, 0)->x, get_list_postition(&game->players, 0)->y);
           // client_send(con, game, &msg);
        }
        //Spare the cpu, 16 =~ 60 fps
        SDL_Delay(16);
    }
    char msg[100]; // Send this to connected device
    sprintf(msg, "2 %d \n",get_list_postition(&game->players, 0)->id);
    //client_DATA(con,game, &msg);
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





