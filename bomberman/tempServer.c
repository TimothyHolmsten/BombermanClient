//
// Created by martin on 4/21/16.
//
#include "tempServer.h"



void initServer()
{
    SDLNet_Init();

    int curID = 0; //Used for unique ID
    int playernum = 0; // Amount of players on server
    SDL_Event event;

    // Set IP address and that this is server
    IPaddress ip;
    if(SDLNet_ResolveHost(&ip,NULL,22222)==-1) //Resolve servers ip, "null" marks this as the server
    {
        printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
        exit(3);
    }

    Data* socketList = NULL;

    char tmp[1400];
    bool running = true;
    SDLNet_SocketSet sockets = SDLNet_AllocSocketSet(MAX_PLAYER); // So we can see if any data is sen from any client
    TCPsocket server = SDLNet_TCP_Open(&ip);

    while(running)
    {
        while(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                running = false;

        TCPsocket  tmpsocket = SDLNet_TCP_Accept(server);

        /*TODO

         Make check for connection seperate function.
         Make check for incomming data seperate function.
         Fix memory bug
         */


        //Check if new connection
        if(tmpsocket)
        {
            if (playernum < MAX_PLAYER)
            {
                SDLNet_TCP_AddSocket(sockets, tmpsocket); //Adds player to list of connections

                add_front(&socketList, tmpsocket, SDL_GetTicks(), curID); // Adds new connection to our connection list
                printf("New connection: %d \n", curID);

                playernum++;
                curID++;
            }else{
                sprintf(tmp, "4\n");

            }

            SDLNet_TCP_Send(tmpsocket, tmp, (int) strlen(tmp)+1);
        }

        //check for incoming data
        while(SDLNet_CheckSockets(sockets,0) > 0)
        {

            for(int i=0; i<list_size(socketList); i++ )
            {
                printf("%d\n",get_list_postition(&socketList,i)->id);
                if(SDLNet_SocketReady(get_list_postition(&socketList,i)->socket))
                {
                    socketList[i].timeout = SDL_GetTicks(); // Client is still connected
                    SDLNet_TCP_Recv(get_list_postition(&socketList,i)->socket, tmp, 1400);
                    int num= (int) tmp[0] - '0';
                    int j = 1;
                    while(tmp[j]>= '0' && tmp[j] <= '9')
                    {
                        num*=10;
                        num+= (int) tmp[j]-'0';
                        j++;
                    }

                    //Check what kind of message client sent

                    if(num==1) //Postition
                    {

                        for(int k=0; k<playernum; k++) //Sends to all connected players except the player that sent the data
                        {
                            if(k==i)
                                continue;
                            SDLNet_TCP_Send(get_list_postition(&socketList,k)->socket,tmp,(int) strlen(tmp)+1);

                        }
                    }

                    else if(num==20) //Disconnect message
                    {
                        for(int k=0; k<playernum; k++) //Sends to all connected players except the player that sent the data
                        {
                            if(k==i)
                                continue;
                            SDLNet_TCP_Send(get_list_postition(&socketList,k)->socket,tmp,(int) strlen(tmp)+1);
                        }
                        SDLNet_TCP_DelSocket(sockets, get_list_postition(&socketList,i)->socket);
                        SDLNet_TCP_Close(get_list_postition(&socketList,i)->socket);

                        //Make data array linked list and delete socket from it here
                        playernum--;
                    }
                }
            }
        }
        /*for(int j=0; j<playernum; j++) // Handles dc'ed player, disconnect after 10 sec
        {
            int timeoutLimit;
            if (SDL_GetTicks() < 5000)
                timeoutLimit = SDL_GetTicks()-500;
            else
                timeoutLimit = SDL_GetTicks() - 5000;
         if(socketList[j].timeout ==-1)
         {
             printf("DC: id % d ",get_list_postition(&socketList,j)->id);
             printf("time %d \n",get_list_postition(&socketList,j)->timeout);
             sprintf(tmp, "3 %d \n", get_list_postition(&socketList,j)->id);
             for(int k=0; k<playernum; k++)
             {

                     SDLNet_TCP_Send(get_list_postition(&socketList,k)->socket,tmp,(int) strlen(tmp)+1);
             }
            SDLNet_TCP_DelSocket(sockets, get_list_postition(&socketList,j)->socket);


            //Make data array linked list and delete socket from it here
            playernum--;
         }
        } */
        SDL_Delay(1);
    }
    for(int i=0; i<playernum; i++)
        SDLNet_TCP_Close(get_list_postition(&socketList,i)->socket);

        clear_list(socketList);
        SDLNet_FreeSocketSet(sockets);
        SDLNet_TCP_Close(server);
        SDLNet_Quit();


}



































































