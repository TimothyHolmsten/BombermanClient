//
// Created by martin on 4/21/16.
//


#include "tempServer.h"


void initServer()
{
    TCPsocket client, server;
    SDLNet_Init();
    IPaddress ip;
    if(SDLNet_ResolveHost(&ip,NULL,21423)==-1) //Resolve servers ip, "null" marks this as the server
    {
        printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
        exit(3);
    }

    server = SDLNet_TCP_Open(&ip); //open server socket for new connections
    if(!server)
    {
        printf("SDLNet_TCP_Open: %s\n",SDLNet_GetError());
        exit(4);
    }


    const char* test = "This is the server!\n"; // Send this to connected device

    int x = 1;
    while(x){
        client=SDLNet_TCP_Accept(server); //Accept connecting devices

        if(client)
        {
            SDLNet_TCP_Send(client,  test, strlen(test)+1); // Sends the data "test", make struct of postion in future
            SDLNet_TCP_Close(client); //Close socket after one transmission
            break;
        }

    }
    SDLNet_TCP_Close(server);


}