#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"


Data * get_list_postition(Data** head, int postion){

    Data* cur_node = *head;

    for(int i=0; i<postion;i++){
        cur_node = cur_node->next;
    }

    return  cur_node;
}

void add_front(Data** head,TCPsocket socket, Uint32 timeout, int id){
    Data* new_node = (Data *)malloc(sizeof(Data));
    Data* cur_node = *head;

    new_node->socket = socket;
    new_node->timeout = timeout;
    new_node->id = id;
    if(!(*head)){
        new_node->next = NULL;
        (*head) = new_node;
    }else{
        while(cur_node->next != NULL) {
            cur_node = cur_node->next;
        }
        cur_node->next= new_node;

    }
    return;
}

void remove_link(Data** head, int value_to_remove){
    Data* temp_node = NULL;
    Data* current_node = (*head);
    if((*head)->id == value_to_remove){
        (*head) = (*head)->next;
    }else{
        while(current_node){
            if(current_node->next != NULL) {
                if (current_node->next->id == value_to_remove) {
                    temp_node = current_node->next;
                    current_node->next = temp_node->next;
                    current_node = temp_node;
                }
            }
            current_node = current_node->next;
        }
    }
    return;
}


int list_size(Data* head) {
    Data* current_node = head;
    int i=0;
    while(current_node){
        i++;
        current_node = current_node->next;
    }

        return i;

}

void display_list(Data* head){
    Data* current_node = head;
    printf("Linked List:\n");
    while(current_node){
        printf("[%d]-->", current_node->id);
        current_node = current_node->next;
    }
}

void clear_list(Data* head)
{
    Data *curNode = head;
    Data *tempNode = NULL;

    while(curNode != NULL)
    {
        tempNode = curNode->next;
        free(curNode);
        curNode = tempNode;
    }
}

void initLinkedList()
{
    Data *socketListHead = NULL;

    add_front(&socketListHead, NULL, SDL_GetTicks(),1);
    add_front(&socketListHead, NULL, SDL_GetTicks(),2);
    add_front(&socketListHead, NULL, SDL_GetTicks(),3);

    display_list(socketListHead);
    int i = list_size(socketListHead);
    clear_list(socketListHead);
    printf("%d",i);
}