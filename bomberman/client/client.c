//
// Created by martin on 4/21/16.
//

#include "client.h"



void initClient(Game *game)
{

    TCPsocket client;
    IPaddress ip;
    SDLNet_Init();
//er
    if(SDLNet_ResolveHost(&ip,"130.237.84.165",22222)==-1) //Change loopback ip to our server IP
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

    game->client = client;
    game->server = server;

    //Make sure we get the firs packet that defines local player
    SDL_Delay(50);
    client_recv(game);
}

void client_EXIT(TCPsocket client){

    SDLNet_TCP_Close(client);
    SDLNet_Quit();
}

void client_recv(Game *game){
    char tmp[1400];
    if(SDLNet_CheckSockets(game->server,0)>0 && SDLNet_SocketReady(game->client)){

        SDLNet_TCP_Recv(game->client, tmp, 1400);
        bool add = true;
        int type, id;
        //Check the type of message and who sent it
        sscanf(tmp, "%d %d",&type, &id);
        printf("type: %d \n", type);
        if (type == 1){
            printf("received start packet\n");
            int x,y, map;
            sscanf(tmp, "1 %d %d %d %d\n", &id, &x,&y, &map);
            printf("%d %d \n", id, map);

            // If there is no players locally, add first as local player, also get and set the map
            if(get_list_postition(&game->players, 0) == NULL)
            {
                create_player(&game->players, &game->player_count, x,y, id);
                get_list_postition(&game->players,0)->local = 1;  //This is how we know this is the local player

                switch(map) {
                    case 0:
                        printf("lvl1\n");
                        game->map = load_map("level1.map");
                        break;
                    case 1:
                        printf("lvl2\n");
                        game->map = load_map("level2.map");
                        break;

                    default:
                        printf("error with map");
                        break;
                }
            }

            //Check if players allready are exist locally
            for(int i=0; i < dlist_size(&game->players); i++)
            {
                if(get_list_postition(&game->players, i)->id == id ){
                    add = false;
                }
            }
            //If not add them
            if (add)
            {
                create_player(&game->players, &game->player_count, x,y, id);
            }


        }
        if (type == 4){
            printf("recived bomb packet\n");
            int x,y;
            sscanf(tmp, "4 %d %d %d\n", &id,&x,&y);
            printf("%d %d %d\n", id,x,y);


            struct _DlistElement *player = get_list_postition(&game->players,get_pos_from_id(&game->players, id));
            player_place_bomb(player, game, x,y);

        }
        if (type == 2 && game->players.element != NULL){
            int tmp2;

            for(int i = 0; i < dlist_size(&game->players); i++){
                if(id== get_list_postition(&game->players,i)->id){
                    sscanf(tmp, "2 %d %f %f \n", &tmp2, &get_list_postition(&game->players,i)->anix, &get_list_postition(&game->players,i)->aniY);
                }
            }
        }

        if (type == 9){
            printf("recived dc packet\n");
            sscanf(tmp, "9 %d \n", &id);
            printf("%d \n", id);

           dlist_removeElement(&game->players,get_pos_from_id(&game->players, id));
            dlist_print(&game->players);

        }
    }
}


void client_send(Game *game, char *msg){
    /*
    int id;
    sscanf(msg, "%d \n", &id);
    if(id == 4)
    printf("%d\n", id);*/
    SDLNet_TCP_Send(game->client,  msg, (int)strlen(msg)+1);

}