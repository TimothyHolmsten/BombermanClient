//
// Created by martin on 4/21/16.
//


#include "tempServer.h"


void initServer()
{
    TCPsocket client, server;
    SDLNet_Init();
    IPaddress ip;
    if(SDLNet_ResolveHost(&ip,NULL,21423)==-1)
    {
        printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
        exit(3);
    }

    server = SDLNet_TCP_Open(&ip);
    if(!server)
    {
        printf("SDLNet_TCP_Open: %s\n",SDLNet_GetError());
        exit(4);
    }


    const char* test = "This is the server!\n";

    int x = 1;
    while(x){
        client=SDLNet_TCP_Accept(server);

        if(client)
        {
            SDLNet_TCP_Send(client,  test, strlen(test)+1);
            SDLNet_TCP_Close(client);
            break;
        }

    }
    SDLNet_TCP_Close(server);


}