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
    printf("Awaiting clients...\n");

    const char* test = "This was sent from the server!\n"; // Send this to connected device
    char buffer[512];
    int x = 1;
    int clientConnected = 0;
    do{

    if (!clientConnected) {
        client = SDLNet_TCP_Accept(server);
        if (client) {

            printf("test\n");
            SDLNet_TCP_Recv(client, buffer, 512); // Recivie packet from server
            printf("%s", buffer);
            clientConnected = 1;
        }
    }

        // If there is activity on our server socket (i.e. a client has trasmitted data to us) then...
        if (clientConnected)
        {
            SDLNet_TCP_Recv(client, buffer, 512); // Recivie packet from server
            int playerX = buffer - '0';


            printf("%s", buffer);
        }
        SDL_Delay(16); //Dont fry the CPU
    }while(x);

    SDLNet_TCP_Close(client); //Close socket after one transmission

    SDLNet_TCP_Close(server);


}