//
// Created by martin on 4/21/16.
//

#include "client.h"



void initClient(connection *con, Game *game)
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
    SDLNet_SocketSet server = SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(server, client);
//c
    con->client = client;
    con->server = server;


    SDL_Delay(50);
    client_recv(con, game);
}

void client_EXIT(TCPsocket client){

    SDLNet_TCP_Close(client);
    SDLNet_Quit();
}
void client_recv(connection *con, Game *game){
    char tmp[1400];
    if(SDLNet_CheckSockets(con->server,0)>0 && SDLNet_SocketReady(con->client)){

        SDLNet_TCP_Recv(con->client, tmp, 1400);
        bool add = true;
        int type, id;
        //Check the type of message and who sent it
        sscanf(tmp, "%d %d",&type, &id);
        if (type == 1){
            printf("recived start packet\n");
            int tmp2;
            int id, x,y;
            sscanf(tmp, "1 %d %d %d \n", &id, &x,&y);
            printf("%d %d %d\n", id, x, y);

            if(get_list_postition(&game->players, 0) == NULL)
            {
                create_player(&game->players, &game->player_count, x,y, id);
                get_list_postition(&game->players,0)->local = 1;  //This is how we know this is the local player
            }

            for(int i=0; i < dlist_size(&game->players); i++)
            {
                if(get_list_postition(&game->players, i)->id == id ){
                    add = false;
                }
            }
            if (add)
            {
                create_player(&game->players, &game->player_count, x,y, id);
            }


        }

        if (type == 2 && game->players.element != NULL){
            int tmp2;

            sscanf(tmp, "2 %d %d %d \n", &tmp2, &get_list_postition(&game->players,1)->x, &get_list_postition(&game->players,1)->y);

            for(int i = 0; i < dlist_size(&game->players); i++){
                if(id== get_list_postition(&game->players,i)->id){

                }
            }
        }
    }
}


void client_send(connection *con, Game *game, char *msg){

    SDLNet_TCP_Send(con->client,  msg, (int)strlen(msg)+1);

}