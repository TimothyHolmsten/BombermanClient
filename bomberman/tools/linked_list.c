#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




void dlist_init(Dlist* list)    // sets the first element to null (because no elements have been created)
{
    list->element = NULL;
}



DlistElement* dlist_createElement(int id, TCPsocket socket, Uint32 timeout)  // Creates the element for the list
{
    DlistElement* element = malloc(sizeof(DlistElement));
    element->id = id;
    element->socket = socket;
    element->timeout= timeout;
    element->next = NULL;

    return element;
}



void dlist_insert_last(Dlist* list, DlistElement* element)
{

    DlistElement* currentElement = list->element;
    //add first
    if(currentElement == NULL)
    {
        list->element = element;
    }
    else
    {
        while(1)
        {
            if(currentElement->next == NULL)
            {
                break;
            }
            currentElement = currentElement->next;
        }

        currentElement->next = element;

    }
}



void dlist_removeAllElements(Dlist *list)
{
    DlistElement* currentElement = list->element;
    int listlength=0;
    while(1)
    {
        listlength++;
        if(currentElement->next == NULL)
        {
            break;
        }
        currentElement = currentElement->next;
    }
    int i;
    for(i = 0;i < listlength; i++)
    {
        dlist_removeElement(list,0);
    }
}

int dlist_removeElement(Dlist *list, int number) // removes a give item from the list
{
    DlistElement* currentElement = list->element;
    DlistElement* deleteElement = NULL;

    int i;
    if(number == 0) // removing the first element
    {
        if(currentElement->next == NULL) // checking if there is only one item in list
        {
            list->element = NULL;   // if it is we just sets it to null(no elements left in the list)
        }
        else    // if not we just link it to the next element
        {
            list->element = currentElement->next;
        }

        free(currentElement);
        return 1;
    }

    for(i=0; i<(number-1); i++) // we want to loop the the element before the one we want to remove
    {
        if(currentElement->next != NULL) // checks if there is a next element.
            currentElement = currentElement->next; // if it is go to that element
        else
            return 0; // if not stop the program (because tried to delete an element that don't exist)
    }
    if(currentElement->next == NULL) // checks if there is a next element.
        return 0;   // if not stop the program (because we have tried to delete an element that don't exist)
    else
        deleteElement = currentElement->next; // sets the next element to deleteElement


    if(deleteElement->next == NULL) //checks if the delete element is the last element
    {
        currentElement->next = NULL;   // if it is we sets the currentElement to the last element
        free(deleteElement);
    }
    else
    {
        currentElement->next = deleteElement->next; // if not we know there is a element after the deleteElement so we assignee that to currentElement next
        free(deleteElement);
    }
    return 0;
}

DlistElement *get_list_postition(Dlist *list, int pos)   // prints the list,totalPrice and totalAmount
{
    int count;
    DlistElement* currentElement = list->element;

    for(int i = 0; i < pos; i++)
    {
        if(currentElement->next)
        currentElement = currentElement->next;
    }

    return currentElement;

}

int dlist_size(Dlist *list)   // prints the list,totalPrice and totalAmount
{
    int count=0;
    DlistElement* currentElement = list->element;

    while(currentElement != NULL)
    {
        currentElement = currentElement->next;
        count++;
    }
    return count;
}

void dlist_print(Dlist *list)   // prints the list,totalPrice and totalAmount
{
    DlistElement* currentElement = list->element;
    while(currentElement != NULL)
    {
        printf("Name: %d\n",currentElement->id);
        currentElement = currentElement->next;
    }
}


