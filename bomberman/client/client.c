//
// Created by martin on 4/21/16.
//

#include "client.h"


void initClient()
{

    TCPsocket client;
    IPaddress ip;
    if(SDLNet_ResolveHost(&ip,"127.0.0.1",21423)==-1) //Change loopback ip to our server IP
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
    char text[100];

    SDLNet_TCP_Recv(client, text,100); // Recivie packet from server

    printf("%s", text);

    SDLNet_TCP_Close(client);

    SDLNet_Quit();
}