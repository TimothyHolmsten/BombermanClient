//
// Created by martin on 4/21/16.
//

#include "client.h"



void initClient(connection *con)
{

    TCPsocket client;
    TCPsocket client2;
    IPaddress ip;
    SDLNet_Init();

    if(SDLNet_ResolveHost(&ip,"130.237.84.165",22222)==-1) //Change loopback ip to our server IP
    {
        printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
        exit(3);
    }

    client = SDLNet_TCP_Open(&ip);      //Open socket, if error occurs exit with error code 9
    client2 = SDLNet_TCP_Open(&ip);
    if(!client)
    {
        printf("SDLNet_TCP_Open: %s\n",SDLNet_GetError());
        exit(9);
    }
    SDLNet_SocketSet server = SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(server, client);

    con->client = client;
    con->client2 = client2;
    con->server = server;
}

void client_EXIT(TCPsocket client){

    SDLNet_TCP_Close(client);
    SDLNet_Quit();
}

void client_DATA(connection *con, Game *game){

    char tmp[1400];
    char test[100]; // Send this to connected device
    int offset=0;
    sprintf(test, "1 %d %d %d \n",game->players[1].id, game->players[0].x +1,game->players[0].y);


            SDLNet_TCP_Send(con->client2,  test, (int)strlen(test)+1);



    if(SDLNet_CheckSockets(con->server,0)>0 && SDLNet_SocketReady(con->client)){

        SDLNet_TCP_Recv(con->client,  tmp, 1400);

        int type, id;
        //Check the type of message and who sent it
        sscanf(tmp, "%d %d",&type, &id);
        if (type == 1){
            for(int i = 0; i < 8; i++){
                if(id== game->players[i].id){
                    int tmp2;

                    sscanf(tmp, "1 %d %d %d \n", &tmp2, &game->players[i].x, &game->players[i].y);

                }
            }
        }
    }





}