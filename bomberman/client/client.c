//
// Created by martin on 4/21/16.
//

#include "client.h"


TCPsocket initClient()
{

    TCPsocket client;
    IPaddress ip;
    SDLNet_Init();
    if(SDLNet_ResolveHost(&ip,"127.0.0.1",22222)==-1) //Change loopback ip to our server IP
    {
        printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
        exit(3);
    }

    client = SDLNet_TCP_Open(&ip);      //Open socket, if error occurs exit with error code 9
    if(!client)
    {
        printf("SDLNet_TCP_Open: %s\n",SDLNet_GetError());
        exit(9);
    }




    return client;


}

void client_EXIT(TCPsocket client){

    SDLNet_TCP_Close(client);
    SDLNet_Quit();
}

void client_DATA(TCPsocket client, int playerX, int playerY){


    char test[100]; // Send this to connected device

    sprintf(test, "1 %d \n",playerX);

    SDLNet_TCP_Send(client,  test, (int)strlen(test)+1); // Sends the data "test", make struct of postion in future


}