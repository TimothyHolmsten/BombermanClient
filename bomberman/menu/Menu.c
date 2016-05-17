//
// Created by martin on 5/17/16.
//
//  Created by Neira C on 2016-04-01.
//  Copyright © 2016 Neira C. All rights reserved.
//
//Allmäna kommentarer: * Alla bilder har datorns lokala sökväg (den hittar inte bilderna när de ligger i
//                       projektmappen
//                     * Samma som ovan fast med textfonter
//                     * Hela programmet ska returnera en array med vald karaktär (siffra som ligger första
//                       platsen av arrayen) och spelarens namn


#include "Menu.h"

#define NROFBUTTONS 3
#define NROFCHARACTERS 8

/*typedef struct gameOptions{
    SDL_Renderer *renderer;
}gameOptions;*/

void show_menu(SDL_Renderer *renderer, SDL_Texture* texture, SDL_Surface * surface, SDL_Rect* menu, SDL_Rect* fullWindow, TTF_Font* font, SDL_Surface* message, SDL_Texture* text, SDL_Color textColor, SDL_Rect header)
{
    // Background
    fullWindow->x = 0;
    fullWindow->y = 0;
    fullWindow->w = 640;
    fullWindow->h = 480;

    menu[0].x = 220;    //Start
    menu[0].y = 120;
    menu[0].w = 200;
    menu[0].h = 80;

    menu[1].x = 220;    //Options
    menu[1].y = 240;
    menu[1].w = 200;
    menu[1].h = 80;

    menu[2].x = 220;    //Help
    menu[2].y = 360;
    menu[2].w = 200;
    menu[2].h = 80;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Black background color
    SDL_RenderFillRect(renderer, fullWindow); // Color background

    SDL_Rect startButton = {220,120,200,80};

    surface = IMG_Load("bomberman/image/images/Start.png");
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_RenderCopy(renderer,texture,NULL,&startButton);

    surface = IMG_Load("bomberman/image/images/Options.png");
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_RenderCopy(renderer,texture,NULL,&menu[1]);

    surface = IMG_Load("bomberman/image/images/Help.png");
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_RenderCopy(renderer,texture,NULL,&menu[2]);

    font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",90);
    message = TTF_RenderText_Blended(font, "BOMBERMAN", textColor);
    text = SDL_CreateTextureFromSurface(renderer, message);
    SDL_QueryTexture(text, NULL, NULL, &header.w, &header.h);
    SDL_RenderCopy(renderer,text,NULL, &header);

    SDL_RenderPresent(renderer);
}

int startMenu(SDL_Window* window,SDL_Renderer* renderer){
    int temp = initMenu(window,renderer);
    return temp;
}

int initMenu(SDL_Window* window,SDL_Renderer* renderer)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    int x, y, chosenButton, again=1;
    Uint32 time;

    char playerInfo[50];


    SDL_Surface * surface = NULL;
    SDL_Texture * texture = NULL;

    //gameOptions *gp;
    //gp->renderer = renderer;

    TTF_Font* font = NULL;
    SDL_Surface* message = NULL;
    SDL_Texture* text = NULL;

    SDL_Rect menu[NROFBUTTONS];
    SDL_Rect fullWindow;

    SDL_Color textColor;
    textColor.r = 36;
    textColor.g = 146;
    textColor.b = 163;

    SDL_Color black;
    black.r = 0;
    black.g = 0;
    black.b = 0;

    SDL_Rect header;   //Header text
    header.x = 25;
    header.y = 0;
    header.w = 70;
    header.h = 30;

    SDL_Rect back;
    back.x = 4;       // Back
    back.y = 1;
    back.w = 64;
    back.h = 32;

    SDL_Rect start[5]; // start
    start[0].x = 200;       // "Enter name:"
    start[0].y = 1;
    start[0].w = 200;
    start[0].h = 80;

    start[1].x = 120;       // NameBox
    start[1].y = 84;
    start[1].w = 370;
    start[1].h = 64;

    start[2].x = 170;       // "Choose character:"
    start[2].y = 180;
    start[2].w = 280;
    start[2].h = 80;

    start[3].x = 220;       // Play
    start[3].y = 360;
    start[3].w = 200;
    start[3].h = 80;

    start[4].x = 125;       // "End with enter"
    start[4].y = 100;
    start[4].w = 360;
    start[4].h = 30;

    SDL_Rect characters[NROFCHARACTERS]; // Characters
    characters[0].x = 20;       // Peach
    characters[0].y = 265;
    characters[0].w = 64;
    characters[0].h = 64;

    characters[1].x = 94;       //Goku
    characters[1].y = 265;
    characters[1].w = 64;
    characters[1].h = 64;

    characters[2].x = 168;      //Blåklänning
    characters[2].y = 265;
    characters[2].w = 64;
    characters[2].h = 64;

    characters[3].x = 242;
    characters[3].y = 265;
    characters[3].w = 64;
    characters[3].h = 64;

    characters[4].x = 316;
    characters[4].y = 265;
    characters[4].w = 64;
    characters[4].h = 64;

    characters[5].x = 390;
    characters[5].y = 265;
    characters[5].w = 64;
    characters[5].h = 64;

    characters[6].x = 464;
    characters[6].y = 265;
    characters[6].w = 64;
    characters[6].h = 64;

    characters[7].x = 538;
    characters[7].y = 265;
    characters[7].w = 64;
    characters[7].h = 64;


    SDL_Rect help[5];
    help[0].x = 165;    //Keybord_wasd
    help[0].y = 150;
    help[0].w = 150;
    help[0].h = 105;

    help[1].x = 5;      //Keyborad_arrows
    help[1].y = 150;
    help[1].w = 150;
    help[1].h = 105;

    help[2].x = 345;    //Keyboard_space
    help[2].y = 185;
    help[2].w = 290;
    help[2].h = 46;

    help[3].x = 5;     //Instruction text
    help[3].y = 260;
    help[3].w = 640;
    help[3].h = 30;

    help[4].x = 5;     //Instruction text
    help[4].y = 290;
    help[4].w = 630;
    help[4].h = 30;





    while(1)
    {

        show_menu(renderer,texture,surface,menu,&fullWindow,font,message,text,textColor,header);

        SDL_Event event;

        while(again == 1)
        {

            time = SDL_GetTicks();
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {

                    case SDL_MOUSEBUTTONDOWN:
                        x = event.button.x;
                        y = event.button.y;

                        for(int i = 0; i < NROFBUTTONS; i++)
                        {
                            if(x>=menu[i].x && x<=menu[i].x+menu[i].w && y>=menu[i].y && y<=menu[i].y+menu[i].h)
                            {
                                chosenButton = i;
                                again = 0;
                                break;
                            }
                        }
                        break;
                    case SDL_KEYDOWN:
                        if(event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            SDL_FreeSurface(surface);
                            SDL_FreeSurface(message);
                            return 0;
                        }
                }
            }
        }

        /********************************** N Ä S T A    M E N Y **********************************/


        if(chosenButton == 0) // START
        {
            again = 2;

            SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &fullWindow);

            font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",40);
            message = TTF_RenderText_Blended(font, "Enter name:", textColor);
            text = SDL_CreateTextureFromSurface(renderer, message);
            SDL_QueryTexture(text, NULL, NULL, 0, 0);
            SDL_RenderCopy(renderer,text,NULL, &start[0]);

            surface = IMG_Load("bomberman/image/images/NameBox.png");
            texture = SDL_CreateTextureFromSurface(renderer,surface);
            SDL_RenderCopy(renderer,texture,NULL,&start[1]);

            message = TTF_RenderText_Blended(font, "Choose character:", textColor);
            text = SDL_CreateTextureFromSurface(renderer, message);
            SDL_QueryTexture(text, NULL, NULL, 0, 0);
            SDL_RenderCopy(renderer,text,NULL, &start[2]);

            if(playerInfo[0] != '\0')
            {
                font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",100);
                message = TTF_RenderText_Blended(font, playerInfo, textColor);
                text = SDL_CreateTextureFromSurface(renderer, message);
                SDL_QueryTexture(text, NULL, NULL, 0, 0);
                SDL_RenderCopy(renderer,text,NULL, &start[1]);
            }
            else if(playerInfo[0] == '\0')
            {
                font = TTF_OpenFont("bomberman/image/images/ArialNarrowItalic.ttf",50);
                message = TTF_RenderText_Blended(font, "End with ENTER", textColor);
                text = SDL_CreateTextureFromSurface(renderer, message);
                SDL_QueryTexture(text, NULL, NULL, 0, 0);
                SDL_RenderCopy(renderer,text,NULL, &start[4]);
            }

            /*font = TTF_OpenFont("/Library/Fonts/ArialNarrowItalic.ttf",50);
            message = TTF_RenderText_Blended(font, "End with ENTER", textColor);
            text = SDL_CreateTextureFromSurface(renderer, message);
            SDL_QueryTexture(text, NULL, NULL, 0, 0);
            SDL_RenderCopy(renderer,text,NULL, &start[4]);*/

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // White color for menu
            for(int i=3;i < NROFCHARACTERS;i++)
            {
                SDL_RenderFillRect(renderer,&characters[i]);
            }

            surface = IMG_Load("bomberman/image/images/Peach.png");
            texture = SDL_CreateTextureFromSurface(renderer,surface);
            SDL_RenderCopy(renderer,texture,NULL,&characters[0]);

            surface = IMG_Load("bomberman/image/images/Goku.png");
            texture = SDL_CreateTextureFromSurface(renderer,surface);
            SDL_RenderCopy(renderer,texture,NULL,&characters[1]);

            surface = IMG_Load("bomberman/image/images/Blåklänning.png");
            texture = SDL_CreateTextureFromSurface(renderer,surface);
            SDL_RenderCopy(renderer,texture,NULL,&characters[2]);

            surface = IMG_Load("bomberman/image/images/Start.png");
            texture = SDL_CreateTextureFromSurface(renderer,surface);
            SDL_RenderCopy(renderer,texture,NULL,&start[3]);

            surface = IMG_Load("bomberman/image/images/Back.png");
            texture = SDL_CreateTextureFromSurface(renderer,surface);
            SDL_RenderCopy(renderer,texture,NULL,&back);


            SDL_RenderPresent(renderer);

            while(again==2)
            {
                char *pPlayerInfo = playerInfo;
                char characterInfo[12];
                char *pCharacterInfo = characterInfo;
                bool selected[NROFCHARACTERS] = {0,0,0,0,0,0,0,0};

                time = SDL_GetTicks();
                while(SDL_PollEvent(&event))
                {
                    switch(event.type)
                    {

                        case SDL_MOUSEMOTION:
                            x = event.motion.x;
                            y = event.motion.y;
                            for(int i = 0; i < NROFCHARACTERS; i += 1) {
                                if(x>=characters[i].x && x<=characters[i].x+characters[i].w && y>=characters[i].y && y<=characters[i].y+characters[i].h)
                                {
                                    if(!selected[i])
                                    {
                                        selected[i] = 1;

                                        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
                                        SDL_RenderFillRect(renderer, &fullWindow);

                                        font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",40);
                                        message = TTF_RenderText_Blended(font, "Enter name:", textColor);
                                        text = SDL_CreateTextureFromSurface(renderer, message);
                                        SDL_QueryTexture(text, NULL, NULL, 0, 0);
                                        SDL_RenderCopy(renderer,text,NULL, &start[0]);

                                        surface = IMG_Load("bomberman/image/images/NameBox.png");
                                        texture = SDL_CreateTextureFromSurface(renderer,surface);
                                        SDL_RenderCopy(renderer,texture,NULL,&start[1]);

                                        message = TTF_RenderText_Blended(font, "Choose character:", textColor);
                                        text = SDL_CreateTextureFromSurface(renderer, message);
                                        SDL_QueryTexture(text, NULL, NULL, 0, 0);
                                        SDL_RenderCopy(renderer,text,NULL, &start[2]);

                                        if(playerInfo[0] != '\0')
                                        {
                                            font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",100);
                                            message = TTF_RenderText_Blended(font, playerInfo, textColor);
                                            text = SDL_CreateTextureFromSurface(renderer, message);
                                            SDL_QueryTexture(text, NULL, NULL, 0, 0);
                                            SDL_RenderCopy(renderer,text,NULL, &start[1]);
                                        }
                                        else if(playerInfo[0] == '\0')
                                        {
                                            font = TTF_OpenFont("bomberman/image/images/ArialNarrowItalic.ttf",50);
                                            message = TTF_RenderText_Blended(font, "End with ENTER", textColor);
                                            text = SDL_CreateTextureFromSurface(renderer, message);
                                            SDL_QueryTexture(text, NULL, NULL, 0, 0);
                                            SDL_RenderCopy(renderer,text,NULL, &start[4]);
                                        }

                                        SDL_SetRenderDrawColor(renderer, 36, 146, 163, 255);
                                        SDL_RenderFillRect(renderer,&characters[i]);

                                        surface = IMG_Load("bomberman/image/images/Peach.png");
                                        texture = SDL_CreateTextureFromSurface(renderer,surface);
                                        SDL_RenderCopy(renderer,texture,NULL,&characters[0]);

                                        surface = IMG_Load("bomberman/image/images/Goku.png");
                                        texture = SDL_CreateTextureFromSurface(renderer,surface);
                                        SDL_RenderCopy(renderer,texture,NULL,&characters[1]);

                                        surface = IMG_Load("bomberman/image/images/Blåklänning.png");
                                        texture = SDL_CreateTextureFromSurface(renderer,surface);
                                        SDL_RenderCopy(renderer,texture,NULL,&characters[2]);

                                        surface = IMG_Load("bomberman/image/images/Start.png");
                                        texture = SDL_CreateTextureFromSurface(renderer,surface);
                                        SDL_RenderCopy(renderer,texture,NULL,&start[3]);

                                        surface = IMG_Load("bomberman/image/images/Back.png");
                                        texture = SDL_CreateTextureFromSurface(renderer,surface);
                                        SDL_RenderCopy(renderer,texture,NULL,&back);

                                        SDL_RenderPresent(renderer);
                                    }
                                }
                                else
                                {
                                    if(selected[i])
                                    {
                                        selected[i] = 0;
                                        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
                                        SDL_RenderFillRect(renderer, &fullWindow);

                                        font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",40);
                                        message = TTF_RenderText_Blended(font, "Enter name:", textColor);
                                        text = SDL_CreateTextureFromSurface(renderer, message);
                                        SDL_QueryTexture(text, NULL, NULL, 0, 0);
                                        SDL_RenderCopy(renderer,text,NULL, &start[0]);

                                        surface = IMG_Load("bomberman/image/images/NameBox.png");
                                        texture = SDL_CreateTextureFromSurface(renderer,surface);
                                        SDL_RenderCopy(renderer,texture,NULL,&start[1]);

                                        message = TTF_RenderText_Blended(font, "Choose character:", textColor);
                                        text = SDL_CreateTextureFromSurface(renderer, message);
                                        SDL_QueryTexture(text, NULL, NULL, 0, 0);
                                        SDL_RenderCopy(renderer,text,NULL, &start[2]);

                                        font = TTF_OpenFont("bomberman/image/images/ArialNarrowItalic.ttf",50);
                                        message = TTF_RenderText_Blended(font, "End with ENTER", textColor);
                                        text = SDL_CreateTextureFromSurface(renderer, message);
                                        SDL_QueryTexture(text, NULL, NULL, 0, 0);
                                        SDL_RenderCopy(renderer,text,NULL, &start[4]);

                                        font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",100);
                                        message = TTF_RenderText_Blended(font, playerInfo, textColor);
                                        text = SDL_CreateTextureFromSurface(renderer, message);
                                        SDL_QueryTexture(text, NULL, NULL, 0, 0);
                                        SDL_RenderCopy(renderer,text,NULL, &start[1]);

                                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // White color for menu
                                        SDL_RenderFillRect(renderer,&characters[i]);

                                        surface = IMG_Load("bomberman/image/images/Peach.png");
                                        texture = SDL_CreateTextureFromSurface(renderer,surface);
                                        SDL_RenderCopy(renderer,texture,NULL,&characters[0]);

                                        surface = IMG_Load("bomberman/image/images/Goku.png");
                                        texture = SDL_CreateTextureFromSurface(renderer,surface);
                                        SDL_RenderCopy(renderer,texture,NULL,&characters[1]);

                                        surface = IMG_Load("bomberman/image/images/Blåklänning.png");
                                        texture = SDL_CreateTextureFromSurface(renderer,surface);
                                        SDL_RenderCopy(renderer,texture,NULL,&characters[2]);

                                        surface = IMG_Load("bomberman/image/images/Start.png");
                                        texture = SDL_CreateTextureFromSurface(renderer,surface);
                                        SDL_RenderCopy(renderer,texture,NULL,&start[3]);

                                        surface = IMG_Load("bomberman/image/images/Back.png");
                                        texture = SDL_CreateTextureFromSurface(renderer,surface);
                                        SDL_RenderCopy(renderer,texture,NULL,&back);
                                    }
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            x = event.button.x;
                            y = event.button.y;

                            if(x>=start[1].x && x<=start[1].x+start[1].w && y>=start[1].y && y<=start[1].y+start[1].h)
                            {
                                SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
                                SDL_RenderFillRect(renderer, &fullWindow);

                                font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",40);
                                message = TTF_RenderText_Blended(font, "Enter name:", textColor);
                                text = SDL_CreateTextureFromSurface(renderer, message);
                                SDL_QueryTexture(text, NULL, NULL, 0, 0);
                                SDL_RenderCopy(renderer,text,NULL, &start[0]);

                                surface = IMG_Load("bomberman/image/images/NameBox.png");
                                texture = SDL_CreateTextureFromSurface(renderer,surface);
                                SDL_RenderCopy(renderer,texture,NULL,&start[1]);

                                font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",40);
                                message = TTF_RenderText_Blended(font, "Choose character:", textColor);
                                text = SDL_CreateTextureFromSurface(renderer, message);
                                SDL_QueryTexture(text, NULL, NULL, 0, 0);
                                SDL_RenderCopy(renderer,text,NULL, &start[2]);


                                SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
                                for(int i=3;i < NROFCHARACTERS;i++)
                                {
                                    SDL_RenderFillRect( renderer, &characters[i]);
                                }

                                surface = IMG_Load("bomberman/image/images/Peach.png");
                                texture = SDL_CreateTextureFromSurface(renderer,surface);
                                SDL_RenderCopy(renderer,texture,NULL,&characters[0]);

                                surface = IMG_Load("bomberman/image/images/Goku.png");
                                texture = SDL_CreateTextureFromSurface(renderer,surface);
                                SDL_RenderCopy(renderer,texture,NULL,&characters[1]);

                                surface = IMG_Load("bomberman/image/images/Blåklänning.png");
                                texture = SDL_CreateTextureFromSurface(renderer,surface);
                                SDL_RenderCopy(renderer,texture,NULL,&characters[2]);

                                surface = IMG_Load("bomberman/image/images/Start.png");
                                texture = SDL_CreateTextureFromSurface(renderer,surface);
                                SDL_RenderCopy(renderer,texture,NULL,&start[3]);

                                surface = IMG_Load("bomberman/image/images/Back.png");
                                texture = SDL_CreateTextureFromSurface(renderer,surface);
                                SDL_RenderCopy(renderer,texture,NULL,&back);

                                SDL_RenderPresent(renderer);


                                while(event.key.keysym.sym != SDLK_RETURN)
                                {
                                    while(SDL_PollEvent(&event))
                                    {
                                        switch(event.type)
                                        {
                                            case SDL_KEYDOWN:
                                                switch (event.key.keysym.sym)
                                                {
                                                    case SDLK_a:
                                                        strcat(playerInfo, "A");
                                                        break;
                                                    case SDLK_b:
                                                        strcat(playerInfo, "B");
                                                        break;
                                                    case SDLK_c:
                                                        strcat(playerInfo, "C");
                                                        break;
                                                    case SDLK_d:
                                                        strcat(playerInfo, "D");
                                                        break;
                                                    case SDLK_e:
                                                        strcat(playerInfo, "E");
                                                        break;
                                                    case SDLK_f:
                                                        strcat(playerInfo, "F");
                                                        break;
                                                    case SDLK_g:
                                                        strcat(playerInfo, "G");
                                                        break;
                                                    case SDLK_h:
                                                        strcat(playerInfo, "H");
                                                        break;
                                                    case SDLK_i:
                                                        strcat(playerInfo, "I");
                                                        break;
                                                    case SDLK_j:
                                                        strcat(playerInfo, "J");
                                                        break;
                                                    case SDLK_k:
                                                        strcat(playerInfo, "K");
                                                        break;
                                                    case SDLK_l:
                                                        strcat(playerInfo, "L");
                                                        break;
                                                    case SDLK_m:
                                                        strcat(playerInfo, "M");
                                                        break;
                                                    case SDLK_n:
                                                        strcat(playerInfo, "N");
                                                        break;
                                                    case SDLK_o:
                                                        strcat(playerInfo, "O");
                                                        break;
                                                    case SDLK_p:
                                                        strcat(playerInfo, "P");
                                                        break;
                                                    case SDLK_q:
                                                        strcat(playerInfo, "Q");
                                                        break;
                                                    case SDLK_r:
                                                        strcat(playerInfo, "R");
                                                        break;
                                                    case SDLK_s:
                                                        strcat(playerInfo, "S");
                                                        break;
                                                    case SDLK_t:
                                                        strcat(playerInfo, "T");
                                                        break;
                                                    case SDLK_u:
                                                        strcat(playerInfo, "U");
                                                        break;
                                                    case SDLK_v:
                                                        strcat(playerInfo, "V");
                                                        break;
                                                    case SDLK_x:
                                                        strcat(playerInfo, "X");
                                                        break;
                                                    case SDLK_y:
                                                        strcat(playerInfo, "Y");
                                                        break;
                                                    case SDLK_z:
                                                        strcat(playerInfo, "Z");
                                                        break;
                                                    case SDLK_BACKSPACE:
                                                        pPlayerInfo[strlen(pPlayerInfo)-1]=0;
                                                        break;
                                                }

                                                SDL_FreeSurface(surface);
                                                SDL_FreeSurface(message);

                                                SDL_RenderClear(renderer);

                                                SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
                                                SDL_RenderFillRect(renderer, &fullWindow);

                                                font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",40);
                                                message = TTF_RenderText_Blended(font, "Enter name:", textColor);
                                                text = SDL_CreateTextureFromSurface(renderer, message);
                                                SDL_QueryTexture(text, NULL, NULL, 0, 0);
                                                SDL_RenderCopy(renderer,text,NULL, &start[0]);

                                                surface = IMG_Load("bomberman/image/images/NameBox.png");
                                                texture = SDL_CreateTextureFromSurface(renderer,surface);
                                                SDL_RenderCopy(renderer,texture,NULL,&start[1]);

                                                font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",40);
                                                message = TTF_RenderText_Blended(font, "Choose character:", textColor);
                                                text = SDL_CreateTextureFromSurface(renderer, message);
                                                SDL_QueryTexture(text, NULL, NULL, 0, 0);
                                                SDL_RenderCopy(renderer,text,NULL, &start[2]);


                                                SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
                                                for(int i=3;i < NROFCHARACTERS;i++)
                                                {
                                                    SDL_RenderFillRect( renderer, &characters[i]);
                                                }

                                                surface = IMG_Load("bomberman/image/images/Peach.png");
                                                texture = SDL_CreateTextureFromSurface(renderer,surface);
                                                SDL_RenderCopy(renderer,texture,NULL,&characters[0]);

                                                surface = IMG_Load("bomberman/image/images/Goku.png");
                                                texture = SDL_CreateTextureFromSurface(renderer,surface);
                                                SDL_RenderCopy(renderer,texture,NULL,&characters[1]);

                                                surface = IMG_Load("bomberman/image/images/Blåklänning.png");
                                                texture = SDL_CreateTextureFromSurface(renderer,surface);
                                                SDL_RenderCopy(renderer,texture,NULL,&characters[2]);

                                                surface = IMG_Load("bomberman/image/images/Start.png");
                                                texture = SDL_CreateTextureFromSurface(renderer,surface);
                                                SDL_RenderCopy(renderer,texture,NULL,&start[3]);

                                                surface = IMG_Load("bomberman/image/images/Back.png");
                                                texture = SDL_CreateTextureFromSurface(renderer,surface);
                                                SDL_RenderCopy(renderer,texture,NULL,&back);

                                                font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",100);
                                                message = TTF_RenderText_Blended(font, playerInfo, textColor);
                                                text = SDL_CreateTextureFromSurface(renderer, message);
                                                SDL_QueryTexture(text, NULL, NULL, 0, 0);
                                                SDL_RenderCopy(renderer,text,NULL, &start[1]);

                                                SDL_RenderPresent(renderer);
                                        }
                                    }
                                }
                            }

                            for(int i = 0; i < NROFCHARACTERS; i++)
                            {
                                if(x>=characters[i].x && x<=characters[i].x+characters[i].w && y>=characters[i].y && y<=characters[i].y+characters[i].h)
                                {
                                    SDL_FreeSurface(surface);
                                    SDL_FreeSurface(message);

                                    pCharacterInfo[strlen(pCharacterInfo)-1]=0;

                                    switch (i)
                                    {
                                        case 0:
                                            memset(characterInfo, 0, 80);
                                            strcat(characterInfo,"0");
                                            break;
                                        case 1:
                                            memset(characterInfo, 0, 80);
                                            strcat(characterInfo,"1");
                                            break;
                                        case 2:
                                            memset(characterInfo, 0, 80);
                                            strcat(characterInfo,"2");
                                            break;
                                        case 3:
                                            memset(characterInfo, 0, 80);
                                            strcat(characterInfo,"3");
                                            break;
                                        case 4:
                                            strcat(characterInfo,"4");
                                            break;
                                        case 5:
                                            strcat(characterInfo,"5");
                                            break;
                                        case 6:
                                            strcat(characterInfo,"6");
                                            break;
                                        case 7:
                                            strcat(characterInfo,"7");
                                            break;
                                    }
                                    break;
                                }
                            }
                            if(x>=back.x && x<=back.x+back.w && y>=back.y && y<=back.y+back.h)
                            {
                                SDL_FreeSurface(surface);
                                SDL_FreeSurface(message);
                                again=1;
                            }
                            if(x>=start[3].x && x<=start[3].x+start[3].w && y>=start[3].y && y<=start[3].y+start[3].h)
                            {
                                strcat(characterInfo,playerInfo);
                                message = TTF_RenderText_Blended(font, characterInfo, textColor);
                                text = SDL_CreateTextureFromSurface(renderer, message);
                                SDL_QueryTexture(text, NULL, NULL, 0, 0);
                                SDL_RenderCopy(renderer,text,NULL, &menu[1]);


                                return 1; // This sends back
                            }
                            break;
                        case SDL_KEYDOWN:
                            if(event.key.keysym.sym == SDLK_ESCAPE)
                            {
                                SDL_FreeSurface(surface);
                                SDL_FreeSurface(message);
                                return 1;
                            }
                    }
                }
            }
        }
        else if(chosenButton == 1) // OPTIONS
        {
            again = 2;

            SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &fullWindow);

            font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",100);
            message = TTF_RenderText_Blended(font, "OPTIONS", textColor);
            text = SDL_CreateTextureFromSurface(renderer, message);
            SDL_QueryTexture(text, NULL, NULL, 0, 0);
            SDL_RenderCopy(renderer,text,NULL, &start[0]);

            surface = IMG_Load("bomberman/image/images/Back.png");
            texture = SDL_CreateTextureFromSurface(renderer,surface);
            SDL_RenderCopy(renderer,texture,NULL,&back);

            SDL_RenderPresent(renderer);

            while(again==2)
            {
                time = SDL_GetTicks();
                while(SDL_PollEvent(&event))
                {
                    switch(event.type)
                    {

                        case SDL_MOUSEBUTTONDOWN:
                            x = event.button.x;
                            y = event.button.y;
                            if(x>=back.x && x<=back.x+back.w && y>=back.y && y<=back.y+back.h)
                            {
                                again=1;
                            }
                            break;
                        case SDL_KEYDOWN:
                            if(event.key.keysym.sym == SDLK_ESCAPE)
                            {
                                SDL_FreeSurface(surface);
                                SDL_FreeSurface(message);
                                return 0;
                            }
                    }
                }
            }
        }
        else if(chosenButton == 2) // HELP
        {
            again = 2;

            SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &fullWindow);

            font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",40);
            message = TTF_RenderText_Blended(font, "HELP", textColor);
            text = SDL_CreateTextureFromSurface(renderer, message);
            SDL_QueryTexture(text, NULL, NULL, 0, 0);
            SDL_RenderCopy(renderer,text,NULL, &start[0]);

            font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",50);
            message = TTF_RenderText_Blended(font, "Use the direction keys above to direct your     Use the  space button to drop a bomb on the", black);
            text = SDL_CreateTextureFromSurface(renderer, message);
            SDL_QueryTexture(text, NULL, NULL, 0, 0);
            SDL_RenderCopy(renderer,text,NULL, &help[3]);

            message = TTF_RenderText_Blended(font, "player in any one of the four cardinal directions.                  position that your player is currently standing on.", black);
            text = SDL_CreateTextureFromSurface(renderer, message);
            SDL_QueryTexture(text, NULL, NULL, 0, 0);
            SDL_RenderCopy(renderer,text,NULL, &help[4]);

            surface = IMG_Load("bomberman/image/images/Keyboard_arrows.png");
            texture = SDL_CreateTextureFromSurface(renderer,surface);
            SDL_RenderCopy(renderer,texture,NULL,&help[0]);

            surface = IMG_Load("bomberman/image/images/Keyboard_wasd.png");
            texture = SDL_CreateTextureFromSurface(renderer,surface);
            SDL_RenderCopy(renderer,texture,NULL,&help[1]);

            surface = IMG_Load("bomberman/image/images/Keyboard_space.png");
            texture = SDL_CreateTextureFromSurface(renderer,surface);
            SDL_RenderCopy(renderer,texture,NULL,&help[2]);

            surface = IMG_Load("bomberman/image/images/Back.png");
            texture = SDL_CreateTextureFromSurface(renderer,surface);
            SDL_RenderCopy(renderer,texture,NULL,&back);

            SDL_RenderPresent(renderer);

            while(again==2)
            {
                time = SDL_GetTicks();
                while(SDL_PollEvent(&event))
                {
                    switch(event.type)
                    {

                        case SDL_MOUSEBUTTONDOWN:
                            SDL_FreeSurface(surface);
                            SDL_FreeSurface(message);
                            x = event.button.x;
                            y = event.button.y;
                            if(x>=back.x && x<=back.x+back.w && y>=back.y && y<=back.y+back.h)
                            {
                                again=1;
                            }
                            break;
                        case SDL_KEYDOWN:
                            if(event.key.keysym.sym == SDLK_ESCAPE)
                            {
                                SDL_FreeSurface(surface);
                                SDL_FreeSurface(message);
                                return 0;
                            }
                    }
                }
            }
        }
    }
}