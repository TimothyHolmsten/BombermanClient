//
// Created by martin on 5/21/16.
//
//would like to change some things like how we get input, and make functions more modular
//but lack of time prevents that
#include "menu.h"

SDL_Rect displayButton(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Texture *texture){
    SDL_Rect pos;
    SDL_Surface *surface;

    pos.x = x;
    pos.y = y;
    pos.h = h;
    pos.w = w;

    SDL_RenderCopyEx(renderer, texture, NULL, &pos, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(texture);
    return pos;
}

void displayText(SDL_Renderer *renderer, char *text,int x, int y, int w, int h, int fontSize ){
    SDL_Rect pos;
    SDL_Color textColor;
    textColor.r = 36;
    textColor.g = 146;
    textColor.b = 163;
    pos.x = x;
    pos.y = y;
    pos.h = h;
    pos.w = w;

    TTF_Font *font = TTF_OpenFont("bomberman/image/images/Krungthep.ttf",fontSize);
    if(font == NULL){
        return;
    }
    SDL_Surface *message = TTF_RenderText_Blended(font, text, textColor);
    SDL_Texture *textRender = SDL_CreateTextureFromSurface(renderer, message);
    SDL_QueryTexture(textRender, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopyEx(renderer,textRender,NULL, &pos, 0 ,NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(textRender);
    SDL_FreeSurface(message);
    TTF_CloseFont(font);
}

int checkButtons(SDL_Rect *buttons, int x, int y, int curMenu){

    for(int i=0; i < sizeof(buttons); i++){
        if(x > buttons[i].x && x < buttons[i].x + buttons[i].w && y > buttons[i].y && y < buttons[i].y + buttons[i].h){
            return i;
        }
    }
    return curMenu;
}

int render_Main_Menu(SDL_Renderer *renderer){
    int mouseX =0;
    int mouseY= 0;
    int buttonPressed = 0;
    SDL_Rect buttons[3];
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background color
    SDL_RenderClear(renderer);

    //Create all the things that needs to be rendered
    displayText(renderer,"BOMBERMAN", 25,0,70,30, 90);
    buttons[0] = displayButton(renderer, 220,120,200,80,load_texture(renderer, "Play.png"));
    buttons[1] = displayButton(renderer, 220,240,200,80,load_texture(renderer, "Options.png"));
    buttons[2] = displayButton(renderer, 220,360,200,80,load_texture(renderer, "Help.png"));
    SDL_RenderPresent(renderer);

    if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT)) {

        buttonPressed=checkButtons(buttons, mouseX,mouseY, 0)+1;
        printf("%d %d %d\n", mouseX, mouseY,buttonPressed);
        SDL_Delay(500);
    }
    return buttonPressed;
}

void get_key_input(char *name,SDL_Rect *characters,SDL_Rect *buttons, int *charSelect, int *menusSelect){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    SDL_Event event;
    int mouseX =0;
    int mouseY= 0;
    while(1) {

        //Checking for mouseclicks
        if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            *charSelect=checkButtons(characters, mouseX,mouseY, 1);
            if(!checkButtons(buttons, mouseX, mouseY, 1)){
                strcpy(name, "");
                strcat(name, event.text.text);
                break;
            }

            SDL_Delay(100);
            return;
        }
        if (state[SDL_SCANCODE_BACKSPACE]) {
            name[strlen(name) - 1] = 0; //Remove last character
            printf("%s\n", name);
            SDL_Delay(200);
            break;
        }
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_Quit();
                exit(2);
            }

            if (event.type == SDL_TEXTINPUT) {
                if (0 == strcmp(name, "Enter nickname")) {
                    strcpy(name, "");
                    strcat(name, event.text.text);
                    break;
                }
                else {
                    if(strlen(name)<14) { //No nicknames longer than 14 characters
                        strcat(name, event.text.text);
                    }
                    break;
                }
            }
        }
    }
}

int render_Menu_Start(SDL_Renderer *renderer, char *name, int *charSelect){
    int characterPadding = 74;
    int inpuText = 1;
    int menusSelect=1;
    SDL_Rect buttons[2];
    SDL_Rect characters[8];
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background color
    SDL_RenderClear(renderer);

    //Render characters
    for(int i=0; i<8; i++){
        characters[i] = displayButton(renderer, 20+characterPadding*i,215, 64,64,load_texture(renderer, "PandaBlueMenu.png"));
    }
    displayText(renderer,"Select your character", 150,150,70,30, 30);
    buttons[0] = displayButton(renderer, 165,50, 310,45,load_texture(renderer, "NameBox.png"));
    buttons[1] = displayButton(renderer, 220,350, 200,80,load_texture(renderer, "Start.png"));

    // By removing the length of the string times 10 we center it, this is kinda ugly since some characters aren't 10 wide
    displayText(renderer,name, 325 - 10 * (int) strlen(name),50,70,30, 30);

    //Highligt around selcted character
    displayButton(renderer, characters[*charSelect].x,characters[*charSelect].y,characters[*charSelect].w-5,characters[*charSelect].h-5, load_texture(renderer,"Panda_selected.png"));

    SDL_RenderPresent(renderer);
    get_key_input(name, characters,buttons, charSelect, &menusSelect);

    return menusSelect;


}


int mainMenu(SDL_Renderer *renderer){
    SDL_Event event;
    char name[20]="Enter nickname";
    int charSelect = 0;
    int running = 1;
    int menuSelect = 0;
    TTF_Init();
    SDL_StartTextInput();

    //While menu is running display the diffrent submenus
    while(running){

        switch (menuSelect){
            case 0:
                menuSelect = render_Main_Menu(renderer);
                break;
            case 1:
                menuSelect = render_Menu_Start(renderer, name, &charSelect);
                break;
            default:
                menuSelect=render_Main_Menu(renderer);
        }


        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running=0;
                SDL_Quit();
                exit(1);
            }
            SDL_Delay(20);
        }
    }
}