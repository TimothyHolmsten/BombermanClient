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


//
//  main.c
//  Game
//
//  Created by Neira C on 2016-04-01.
//  Copyright © 2016 Neira C. All rights reserved.


//TODO Martin
//05-20 implement their code in to the game
//05-20 can't seem to get it to work properly too many bugs
//05-21 made a new menu from scratch, can't solve memory bugs... too much code + all hardcoded pathways
//05-21 copied the original code back here so the changes i made aren't here and implemented the new menu instead
//felt like it was less work

#include "Menu.h"

typedef struct parameters
{
    char name[11];
    int x,y,character,missingInput,showEndWithEnter;


    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event event;
    TTF_Font* font;
    TTF_Font* fontNarrow;
    SDL_Rect menu[NROFBUTTONS],fullWindow, header, back, start[5], characters[NROFCHARACTERS], help[6];

    SDL_Color blueColor, blackColor, redColor;

    SDL_Surface* startButton;
    SDL_Surface* optionButton;
    SDL_Surface* helpButton;
    SDL_Surface* bomberman;

    SDL_Surface* enterName;
    SDL_Surface* obsEnterName;
    SDL_Surface* nameBox;
    SDL_Surface* chooseCharacter;
    SDL_Surface* obsChooseCharacter;
    SDL_Surface* nameSurface;
    SDL_Surface* endWithEnter;

    SDL_Surface* whitePanda;
    SDL_Surface* bluePanda;
    SDL_Surface* yellowPanda;
    SDL_Surface* pinkPanda;
    SDL_Surface* brownPanda;
    SDL_Surface* orangePanda;
    SDL_Surface* greenPanda;
    SDL_Surface* purplePanda;
    SDL_Surface* selectedPanda;
    SDL_Surface* selectedPandaNotpressed;
    SDL_Surface* play;
    SDL_Surface* backButton;

    SDL_Surface* helpHeader;
    SDL_Surface* instruction1;
    SDL_Surface* instruction2;
    SDL_Surface* instruction3;
    SDL_Surface* keyboardArrows;
    SDL_Surface* keyboardWasd;
    SDL_Surface* keyboardSpace;

    SDL_Surface* options;
    SDL_Texture* texture;
}Parameters;

void load_all(Parameters *ap);
void show_menu(Parameters *ap);
void show_start(Parameters *ap);
void show_options(Parameters *ap);
void show_help(Parameters *ap);
void get_name(Parameters *ap);
void get_character(Parameters *ap, int i);
void check_input(Parameters *ap);
void sdl_FreeEverything(Parameters *ap);


int get_playerInfo(Parameters *ap)
{
    int chosenButton, backPressed=1;
    ap->character=8;

    Uint32 time;
    TTF_Init();

    load_all(ap);

    while(1)
    {
        show_menu(ap);

        while(backPressed == 1)
        {
            time = SDL_GetTicks();
            while(SDL_PollEvent(&ap->event))
            {
                switch(ap->event.type)
                {
                    case SDL_QUIT:
                        return 1;
                    case SDL_MOUSEBUTTONDOWN:
                        ap->x = ap->event.button.x;
                        ap->y = ap->event.button.y;

                        for(int i = 0; i < NROFBUTTONS; i++)
                        {
                            if(ap->x>=ap->menu[i].x && ap->x<=ap->menu[i].x+ap->menu[i].w && ap->y>=ap->menu[i].y && ap->y<=ap->menu[i].y+ap->menu[i].h)
                            {
                                chosenButton = i;
                                backPressed = 0;
                                break;
                            }
                        }
                        break;
                    case SDL_KEYDOWN:
                        if(ap->event.key.keysym.sym == SDLK_ESCAPE)
                            return 0;
                }
            }
        }

        /********************************** N Ä S T A    M E N Y **********************************/


        if(chosenButton == START)
        {
            backPressed = 2;
            ap->showEndWithEnter=0;

            show_start(ap);
            SDL_RenderPresent(ap->renderer);

            while(backPressed==2)
            {
                bool selected[NROFCHARACTERS] = {0};

                time = SDL_GetTicks();
                while(SDL_PollEvent(&ap->event))
                {
                    switch(ap->event.type)
                    {
                        case SDL_QUIT:
                            return 1;
                        case SDL_MOUSEMOTION:
                            ap->x = ap->event.motion.x;
                            ap->y = ap->event.motion.y;
                            for(int i = 0; i < NROFCHARACTERS; i++)
                            {
                                if(ap->x>=ap->characters[i].x && ap->x<=ap->characters[i].x+ap->characters[i].w && ap->y>=ap->characters[i].y && ap->y<=ap->characters[i].y+ap->characters[i].h)
                                {
                                    if(!selected[i])
                                    {
                                        selected[i] = 1;

                                        show_start(ap);
                                        ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->selectedPandaNotpressed);
                                        SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->characters[i]);

                                        ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->selectedPanda);
                                        SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->characters[ap->character]);

                                        SDL_RenderPresent(ap->renderer);
                                    }
                                }
                                else
                                {
                                    if(selected[i])
                                        selected[i] = 0;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(ap->x>=ap->start[NAMEBOX].x && ap->x<=ap->start[NAMEBOX].x+ap->start[NAMEBOX].w && ap->y>=ap->start[NAMEBOX].y && ap->y<=ap->start[NAMEBOX].y+ap->start[NAMEBOX].h)
                            {
                                get_name(ap);
                            }
                            for(int i = 0; i < NROFCHARACTERS; i++)
                            {
                                if(ap->x>=ap->characters[i].x && ap->x<=ap->characters[i].x+ap->characters[i].w && ap->y>=ap->characters[i].y && ap->y<=ap->characters[i].y+ap->characters[i].h)
                                {
                                    get_character(ap,i);
                                    show_start(ap);
                                    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->selectedPanda);
                                    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->characters[i]);
                                    SDL_RenderPresent(ap->renderer);
                                }
                            }
                            if(ap->x>=ap->back.x && ap->x<=ap->back.x+ap->back.w && ap->y>=ap->back.y && ap->y<=ap->back.y+ap->back.h)
                            {
                                backPressed=1;
                            }
                            if(ap->x>=ap->start[PLAY].x && ap->x<=ap->start[PLAY].x+ap->start[PLAY].w && ap->y>=ap->start[PLAY].y && ap->y<=ap->start[PLAY].y+ap->start[PLAY].h)
                            {
                                check_input(ap);

                                if(ap->missingInput==0)
                                    break;

                                TTF_CloseFont(ap->font);
                                TTF_CloseFont(ap->fontNarrow);
                                return 0;
                            }
                            break;
                        case SDL_KEYDOWN:
                            if(ap->event.key.keysym.sym == SDLK_ESCAPE)
                                return 1;
                    }
                }
            }
        }

        else if(chosenButton == OPTIONS)
        {
            backPressed = 2;

            show_options(ap);

            while(backPressed==2)
            {
                time = SDL_GetTicks();
                while(SDL_PollEvent(&ap->event))
                {
                    switch(ap->event.type)
                    {
                        case SDL_QUIT:
                            return 1;
                        case SDL_MOUSEBUTTONDOWN:
                            if(ap->x>=ap->back.x && ap->x<=ap->back.x+ap->back.w && ap->y>=ap->back.y && ap->y<=ap->back.y+ap->back.h)
                                backPressed=1;
                            break;
                        case SDL_KEYDOWN:
                            if(ap->event.key.keysym.sym == SDLK_ESCAPE)
                                return 0;
                    }
                }
            }
        }

        else if(chosenButton == HELP)
        {
            backPressed = 2;

            show_help(ap);

            while(backPressed==2)
            {
                time = SDL_GetTicks();
                while(SDL_PollEvent(&ap->event))
                {
                    switch(ap->event.type)
                    {
                        case SDL_QUIT:
                            return 1;
                        case SDL_MOUSEBUTTONDOWN:
                            if(ap->x>=ap->back.x && ap->x<=ap->back.x+ap->back.w && ap->y>=ap->back.y && ap->y<=ap->back.y+ap->back.h)
                                backPressed=1;
                            break;
                        case SDL_KEYDOWN:
                            if(ap->event.key.keysym.sym == SDLK_ESCAPE)
                                return 1;
                    }
                }
            }
        }
    }
}





int mainM()
{
    Parameters ap; //all parameters
    int status;

    status=get_playerInfo(&ap);

    if (status==1)
    {
        return 1;
    }
    else if (status == 0)
    {
        printf("Name: %s \nCharacter: %d \n", ap.name, ap.character);
        return 0;
    }
}






void load_all(Parameters *ap)
{
    ap->window = SDL_CreateWindow("Bomberman menu", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                  640,480,SDL_WINDOW_SHOWN);
    ap->renderer = SDL_CreateRenderer( ap->window, -1, SDL_RENDERER_ACCELERATED);

    ap->blueColor.r = 36;
    ap->blueColor.g = 146;
    ap->blueColor.b = 163;

    ap->blackColor.r = 0;
    ap->blackColor.g = 0;
    ap->blackColor.b = 0;

    ap->redColor.r = 255;
    ap->redColor.g = 0;
    ap->redColor.b = 0;

    ap->font = TTF_OpenFont("/Library/Fonts/Krungthep.ttf",100);
    ap->fontNarrow = TTF_OpenFont("/Library/Fonts/ArialNarrowItalic.ttf",50);

    ap->startButton = IMG_Load("/Users/Neira1/Documents/Start.png");
    ap->helpButton = IMG_Load("/Users/Neira1/Documents/Help.png");
    ap->optionButton = IMG_Load("/Users/Neira1/Documents/Options.png");
    ap->bomberman = TTF_RenderText_Blended(ap->font, "BOMBERMAN", ap->blueColor);

    ap->enterName = TTF_RenderText_Blended(ap->font, "Enter name:", ap->blueColor);
    ap->obsEnterName = TTF_RenderText_Blended(ap->font, "Enter name:", ap->redColor);
    ap->nameBox = IMG_Load("/Users/Neira1/Documents/NameBox.png");
    ap->chooseCharacter = TTF_RenderText_Blended(ap->font, "Choose character:", ap->blueColor);
    ap->obsChooseCharacter = TTF_RenderText_Blended(ap->font, "Choose character:", ap->redColor);
    ap->nameSurface = TTF_RenderText_Blended(ap->font, ap->name, ap->blueColor);
    ap->endWithEnter = TTF_RenderText_Blended(ap->fontNarrow, "End with ENTER", ap->blueColor);
    ap->whitePanda = IMG_Load("/Users/Neira1/Desktop/Panda_white.png");
    ap->bluePanda = IMG_Load("/Users/Neira1/Desktop/Panda_blue.png");
    ap->yellowPanda = IMG_Load("/Users/Neira1/Desktop/Panda_yellow.png");
    ap->pinkPanda = IMG_Load("/Users/Neira1/Desktop/Panda_pink.png");
    ap->brownPanda = IMG_Load("/Users/Neira1/Desktop/Panda_brown.png");
    ap->orangePanda = IMG_Load("/Users/Neira1/Desktop/Panda_orange.png");
    ap->greenPanda = IMG_Load("/Users/Neira1/Desktop/Panda_green.png");
    ap->purplePanda = IMG_Load("/Users/Neira1/Desktop/Panda_purple.png");
    ap->selectedPanda = IMG_Load("/Users/Neira1/Desktop/Panda_selected_notpressed.png");
    ap->selectedPandaNotpressed = IMG_Load("/Users/Neira1/Desktop/Panda_selected.png");
    ap->play = IMG_Load("/Users/Neira1/Documents/Play.png");
    ap->backButton = IMG_Load("/Users/Neira1/Documents/Back.png");

    ap->helpHeader = TTF_RenderText_Blended(ap->font, "HELP", ap->blueColor);
    ap->instruction1 = TTF_RenderText_Blended(ap->font, "Use the direction keys above to        Use the space button to drop", ap->blackColor);
    ap->instruction2 = TTF_RenderText_Blended(ap->font, "direct your player in any one         a bomb on the position that", ap->blackColor);
    ap->instruction3 = TTF_RenderText_Blended(ap->font, "of the four cardinal directions.    your player is standing on.", ap->blackColor);
    ap->keyboardArrows = IMG_Load("/Users/Neira1/Documents/Keyboard_arrows.png");
    ap->keyboardWasd = IMG_Load("/Users/Neira1/Documents/Keyboard_wasd.png");
    ap->keyboardSpace = IMG_Load("/Users/Neira1/Documents/Keyboard_space.png");

    ap->options = TTF_RenderText_Blended(ap->font, "OPTIONS", ap->blueColor);
}

void show_menu(Parameters *ap)
{
    ap->fullWindow.x = 0;
    ap->fullWindow.y = 0;
    ap->fullWindow.w = 640;
    ap->fullWindow.h = 480;

    ap->header.x = 0;
    ap->header.y = 0;
    ap->header.w = 60;
    ap->header.h = 30;

    ap->menu[START].x = 220;
    ap->menu[START].y = 120;
    ap->menu[START].w = 200;
    ap->menu[START].h = 80;

    ap->menu[OPTIONS].x = 220;
    ap->menu[OPTIONS].y = 240;
    ap->menu[OPTIONS].w = 200;
    ap->menu[OPTIONS].h = 80;

    ap->menu[HELP].x = 220;
    ap->menu[HELP].y = 360;
    ap->menu[HELP].w = 200;
    ap->menu[HELP].h = 80;

    SDL_SetRenderDrawColor(ap->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(ap->renderer, &ap->fullWindow);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->startButton);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->menu[START]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->optionButton);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->menu[OPTIONS]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->helpButton);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->menu[HELP]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->bomberman);
    SDL_QueryTexture(ap->texture, NULL, NULL, &ap->header.w, &ap->header.h);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL, &ap->header);

    SDL_RenderPresent(ap->renderer);
}

void show_start(Parameters *ap)
{
    ap->start[ENTERNAME].x = 200;
    ap->start[ENTERNAME].y = 1;
    ap->start[ENTERNAME].w = 200;
    ap->start[ENTERNAME].h = 80;

    ap->start[NAMEBOX].x = 120;
    ap->start[NAMEBOX].y = 84;
    ap->start[NAMEBOX].w = 370;
    ap->start[NAMEBOX].h = 64;

    ap->start[CHOOSECHARACTER].x = 170;
    ap->start[CHOOSECHARACTER].y = 180;
    ap->start[CHOOSECHARACTER].w = 280;
    ap->start[CHOOSECHARACTER].h = 80;

    ap->start[PLAY].x = 220;
    ap->start[PLAY].y = 360;
    ap->start[PLAY].w = 200;
    ap->start[PLAY].h = 80;

    ap->start[ENDWITHENTER].x = 125;
    ap->start[ENDWITHENTER].y = 100;
    ap->start[ENDWITHENTER].w = 360;
    ap->start[ENDWITHENTER].h = 30;

    ap->characters[0].x = 20;
    ap->characters[0].y = 265;
    ap->characters[0].w = 64;
    ap->characters[0].h = 64;

    ap->characters[1].x = 94;
    ap->characters[1].y = 265;
    ap->characters[1].w = 64;
    ap->characters[1].h = 64;

    ap->characters[2].x = 168;
    ap->characters[2].y = 265;
    ap->characters[2].w = 64;
    ap->characters[2].h = 64;

    ap->characters[3].x = 242;
    ap->characters[3].y = 265;
    ap->characters[3].w = 64;
    ap->characters[3].h = 64;

    ap->characters[4].x = 316;
    ap->characters[4].y = 265;
    ap->characters[4].w = 64;
    ap->characters[4].h = 64;

    ap->characters[5].x = 390;
    ap->characters[5].y = 265;
    ap->characters[5].w = 64;
    ap->characters[5].h = 64;

    ap->characters[6].x = 464;
    ap->characters[6].y = 265;
    ap->characters[6].w = 64;
    ap->characters[6].h = 64;

    ap->characters[7].x = 538;
    ap->characters[7].y = 265;
    ap->characters[7].w = 64;
    ap->characters[7].h = 64;

    ap->back.x = 4;
    ap->back.y = 1;
    ap->back.w = 64;
    ap->back.h = 32;

    SDL_SetRenderDrawColor(ap->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(ap->renderer, &ap->fullWindow);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->enterName);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL, &ap->start[ENTERNAME]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->nameBox);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->start[NAMEBOX]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->chooseCharacter);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL, &ap->start[CHOOSECHARACTER]);

    if(ap->name[0] != '\0')
    {
        ap->nameSurface = TTF_RenderText_Blended(ap->font, ap->name, ap->blueColor);
        ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->nameSurface);
        SDL_RenderCopy(ap->renderer,ap->texture,NULL, &ap->start[NAMEBOX]);
    }
    else if(ap->name[0] == '\0' && !ap->showEndWithEnter)
    {
        ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->endWithEnter);
        SDL_RenderCopy(ap->renderer,ap->texture,NULL, &ap->start[ENDWITHENTER]);
    }

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->whitePanda);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->characters[0]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->bluePanda);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->characters[1]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->yellowPanda);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->characters[2]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->pinkPanda);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->characters[3]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->brownPanda);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->characters[4]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->orangePanda);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->characters[5]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->greenPanda);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->characters[6]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->purplePanda);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->characters[7]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->play);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->start[PLAY]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->backButton);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->back);
}

void show_options(Parameters *ap)
{
    SDL_SetRenderDrawColor(ap->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(ap->renderer, &ap->fullWindow);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->options);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL, &ap->start[0]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->backButton);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->back);

    SDL_RenderPresent(ap->renderer);
}

void get_name(Parameters *ap)
{
    char *pname = ap->name;
    ap->showEndWithEnter=1;

    show_start(ap);
    SDL_RenderPresent(ap->renderer);

    while(ap->event.key.keysym.sym != SDLK_RETURN)
    {
        while(SDL_PollEvent(&ap->event))
        {
            switch(ap->event.type)
            {
                case SDL_KEYDOWN:
                    switch (ap->event.key.keysym.sym)
                    {
                        case SDLK_a:
                            strcat(ap->name, "A");
                            break;
                        case SDLK_b:
                            strcat(ap->name, "B");
                            break;
                        case SDLK_c:
                            strcat(ap->name, "C");
                            break;
                        case SDLK_d:
                            strcat(ap->name, "D");
                            break;
                        case SDLK_e:
                            strcat(ap->name, "E");
                            break;
                        case SDLK_f:
                            strcat(ap->name, "F");
                            break;
                        case SDLK_g:
                            strcat(ap->name, "G");
                            break;
                        case SDLK_h:
                            strcat(ap->name, "H");
                            break;
                        case SDLK_i:
                            strcat(ap->name, "I");
                            break;
                        case SDLK_j:
                            strcat(ap->name, "J");
                            break;
                        case SDLK_k:
                            strcat(ap->name, "K");
                            break;
                        case SDLK_l:
                            strcat(ap->name, "L");
                            break;
                        case SDLK_m:
                            strcat(ap->name, "M");
                            break;
                        case SDLK_n:
                            strcat(ap->name, "N");
                            break;
                        case SDLK_o:
                            strcat(ap->name, "O");
                            break;
                        case SDLK_p:
                            strcat(ap->name, "P");
                            break;
                        case SDLK_q:
                            strcat(ap->name, "Q");
                            break;
                        case SDLK_r:
                            strcat(ap->name, "R");
                            break;
                        case SDLK_s:
                            strcat(ap->name, "S");
                            break;
                        case SDLK_t:
                            strcat(ap->name, "T");
                            break;
                        case SDLK_u:
                            strcat(ap->name, "U");
                            break;
                        case SDLK_v:
                            strcat(ap->name, "V");
                            break;
                        case SDLK_x:
                            strcat(ap->name, "X");
                            break;
                        case SDLK_y:
                            strcat(ap->name, "Y");
                            break;
                        case SDLK_z:
                            strcat(ap->name, "Z");
                            break;
                        case SDLK_BACKSPACE:
                            pname[strlen(pname)-1]=0;
                            break;
                    }
                    SDL_RenderClear(ap->renderer);
                    show_start(ap);
                    SDL_RenderPresent(ap->renderer);
            }
        }
    }
}

void get_character(Parameters *ap, int i)
{
    ap->character=8; // Clear in case a choise already has been made

    switch(i)
    {
        case 0:
            ap->character=0;
            break;
        case 1:
            ap->character=1;
            break;
        case 2:
            ap->character=2;
            break;
        case 3:
            ap->character=3;
            break;
        case 4:
            ap->character=4;
            break;
        case 5:
            ap->character=5;
            break;
        case 6:
            ap->character=6;
            break;
        case 7:
            ap->character=7;
            break;
    }
}

void check_input(Parameters *ap)
{
    ap->missingInput=1;

    if(ap->character == 8 && ap->name[0] == '\0')
    {
        ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->obsChooseCharacter);
        SDL_RenderCopy(ap->renderer,ap->texture,NULL, &ap->start[CHOOSECHARACTER]);
        ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->obsEnterName);
        SDL_RenderCopy(ap->renderer,ap->texture,NULL, &ap->start[ENTERNAME]);
        SDL_RenderPresent(ap->renderer);
        ap->missingInput=0;
    }
    if(ap->character == 8) // No chosen character
    {
        ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->obsChooseCharacter);
        SDL_RenderCopy(ap->renderer,ap->texture,NULL, &ap->start[CHOOSECHARACTER]);
        SDL_RenderPresent(ap->renderer);
        ap->missingInput=0;
    }
    if(ap->name[0] == '\0') // No entered name
    {
        ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->obsEnterName);
        SDL_RenderCopy(ap->renderer,ap->texture,NULL, &ap->start[ENTERNAME]);
        SDL_RenderPresent(ap->renderer);
        ap->missingInput=0;
    }
}

void show_help(Parameters *ap)
{
    ap->help[KEYBOARD_WASD].x = 5;
    ap->help[KEYBOARD_WASD].y = 150;
    ap->help[KEYBOARD_WASD].w = 150;
    ap->help[KEYBOARD_WASD].h = 105;

    ap->help[KEYBOARD_ARROWS].x = 165;
    ap->help[KEYBOARD_ARROWS].y = 150;
    ap->help[KEYBOARD_ARROWS].w = 150;
    ap->help[KEYBOARD_ARROWS].h = 105;

    ap->help[KEYBOARD_SPACE].x = 345;
    ap->help[KEYBOARD_SPACE].y = 185;
    ap->help[KEYBOARD_SPACE].w = 290;
    ap->help[KEYBOARD_SPACE].h = 46;

    ap->help[3].x = 5;     //Instruction text
    ap->help[3].y = 260;
    ap->help[3].w = 630;
    ap->help[3].h = 30;

    ap->help[4].x = 5;     //Instruction text
    ap->help[4].y = 290;
    ap->help[4].w = 630;
    ap->help[4].h = 30;

    ap->help[5].x = 5;     //Instruction text
    ap->help[5].y = 320;
    ap->help[5].w = 630;
    ap->help[5].h = 30;

    ap->back.x = 4;
    ap->back.y = 1;
    ap->back.w = 64;
    ap->back.h = 32;

    SDL_SetRenderDrawColor(ap->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(ap->renderer, &ap->fullWindow);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->helpHeader);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL, &ap->start[0]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->instruction1);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL, &ap->help[3]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->instruction2);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL, &ap->help[4]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer, ap->instruction3);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL, &ap->help[5]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->keyboardArrows);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->help[KEYBOARD_ARROWS]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->keyboardWasd);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->help[KEYBOARD_WASD]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->keyboardSpace);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->help[KEYBOARD_SPACE]);

    ap->texture = SDL_CreateTextureFromSurface(ap->renderer,ap->backButton);
    SDL_RenderCopy(ap->renderer,ap->texture,NULL,&ap->back);

    SDL_RenderPresent(ap->renderer);
}