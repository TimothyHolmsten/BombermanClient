//
// Created by Timothy Friberg Holmsten on 19/04/16.
//

#include <SDL_ttf.h>
#include "game.h"
#include "renderer/player/renderPlayer.h"
#include "renderer/object/renderObject.h"

struct thread_arguments{
    Map * map;
    DlistElement * player;
    Game * game;
};

void * thread_update_player(void * arg) {

    struct thread_arguments *arguments = (struct thread_arguments*) arg;
    int i = 1;
    Uint32 playerUpdate = 0;
    while (i) {
        //Only  check for input if, player has been created, player is alive and finally only if a game is running
        if (get_list_postition(&arguments->game->players, 0) != NULL && get_list_postition(&arguments->game->players, 0)->alive == 1 && arguments->game->gameRunning == 1){
            update_local_player(arguments->player, arguments->map, arguments->game, &playerUpdate);
        }
        SDL_Delay(16);
    }

    return NULL;
}
void * thread_multiplayer(void * arg) {
    //Multiplayer
    struct thread_arguments *arguments = (struct thread_arguments*) arg;
    int i = 1;
    while (i) {
        client_recv(arguments->game);
        SDL_Delay(1); //Spare cpu but don't miss a packet
    }

    return NULL;
}

void * thread_update_bombs(void * arg) {

    struct thread_arguments *arguments = (struct thread_arguments*) arg;
    int i = 1;
    while (i) {
        if (get_list_postition(&arguments->game->players, 0) != NULL) {
            for (int k = 0; k < dlist_size(&arguments->game->players); k++) {
                update_bombs(get_list_postition(&arguments->game->players, k)->bombs, arguments->map);
            }
        }
        SDL_Delay(16);
    }

    return NULL;
}

int init_game(SDL_Window *window, SDL_Renderer *renderer, Game * game) {

    initClient(game);
    pthread_t t1, t2,t3;

    struct thread_arguments local_p_data;
    local_p_data.map = &game->map;
    local_p_data.player = get_list_postition(&game->players, 0);
    local_p_data.game = game;
    pthread_create(&t1, NULL, thread_update_player, &local_p_data);
    pthread_create(&t2, NULL, thread_update_bombs, &local_p_data);
    pthread_create(&t3, NULL, thread_multiplayer, &local_p_data);

    game_loop(window, renderer, game);

    pthread_cancel(t1);
    pthread_cancel(t2);
    pthread_cancel(t3);

    return 1;
}

void checkWin(Game *game, SDL_Renderer *renderer, int *lost, int *running){
    SDL_Rect buttons[1];
    int mouseX =0;
    int mouseY= 0;
    int buttonPressed = 0;
    if(get_list_postition(&game->players, 0)->alive==1 && get_list_postition(&game->players, 0)->next == NULL && game->gameRunning != 0 ){
        displayButton(renderer, 430,180, 140,45,load_texture(renderer, "NameBox.png"));
        displayText(renderer,"Victory", 440,182,70,30, 30);
        buttons[0] = displayButton(renderer, 395, 260, 200, 80, load_texture(renderer, "Start.png"));
    }
    if(get_list_postition(&game->players, 0)->alive==0 ){
        displayButton(renderer, 430,180, 140,45,load_texture(renderer, "NameBox.png"));
        displayText(renderer,"Defeat", 440,182,70,30, 30);
        buttons[0] = displayButton(renderer, 395, 260, 200, 80, load_texture(renderer, "Start.png"));
    }

    if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT)) {

        buttonPressed = checkButtons(buttons, mouseX, mouseY, 2, 1) + 1;
        if (buttonPressed == 1) {
            char msg[100]; // Send this to connected all other players so they know game has begun
            sprintf(msg, "3 %d\n", get_list_postition(&game->players, 0)->id);
            client_send(game, &msg);
            *running = 0;

        }
    }
}

void check_start(SDL_Renderer *renderer, Game *game){
    SDL_Rect buttons[3];
    int mouseX =0;
    int mouseY= 0;
    int buttonPressed = 0;
    buttons[1] = displayButton(renderer, 310,220, 380,45,load_texture(renderer, "NameBox.png"));
    displayText(renderer,"Waiting for players...", 330,220,70,30, 30);
    buttons[2] = displayButton(renderer, 455,280, 80,45,load_texture(renderer, "NameBox.png"));
    char msg1[10];
    sprintf(msg1, "%d/8", game->player_count);
    displayText(renderer,msg1, 465,285,70,30, 30);
    if (get_list_postition(&game->players, 0)->id == 0) {
        buttons[0] = displayButton(renderer, 395, 120, 200, 80, load_texture(renderer, "Start.png"));

        if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT) && game->player_count > 1) {

            buttonPressed = checkButtons(buttons, mouseX, mouseY, 2, 1) + 1;
            if (buttonPressed == 1) {
                printf("button");
                char msg[100]; // Send this to connected all other players so they know game has begun
                sprintf(msg, "8 \n");
                client_send(game, &msg);

            }
        }
    }
}

int game_loop(SDL_Window *window, SDL_Renderer *renderer, Game * game) {

    int running = 1;
    SDL_Event event;
    SDL_MouseButtonEvent mouseEvent;
    int won =0; int lost = 0;
    //Things for the 'start' button

    while (running==1)
    {

        //Clear screen
        SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
        SDL_RenderClear(renderer);

        //render all element from bottom and up
        if(get_list_postition(&game->players, 0) != NULL) {
            render_grass(window);
            render_walls(window, game);
            render_boxes(window, game);
            render_bombs(window, game);
            render_players(window, game);
            render_explosion(window,game);

            //Host will have a button "start" with the ability to start a game
            if(game->gameRunning == 0 ) {
                check_start(renderer,game); //Simple function that checks if you can start the game or not
                //If there are 2 players or more, and u were the first one to connect ("host")
                // then you can start the match
            }
        }
        checkWin(game, renderer , &lost, &running);
        //Show whats rendered
        SDL_RenderPresent(renderer);

        //If you press on exit close game and send dc message
        if(SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                char msg[100]; // Send this to connected device
                sprintf(msg, "3 %d\n", get_list_postition(&game->players, 0)->id);
                client_send(game, &msg);

                running = 0;
            }
        }
        //Spare the cpu, 16 =~ 60 fps
        SDL_Delay(16);
    }


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





