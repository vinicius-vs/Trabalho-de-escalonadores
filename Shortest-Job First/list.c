/**
 * Various list operations
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"
#include "task.h"


// add a new task to the list of tasks
void insert(struct node **head, Task *newTask) {
    struct  node * newNode = malloc(sizeof(struct node)); // crie um novo espaço na memoria
    newNode->task = newTask; //Adicionado a nova tesk no espaço de memória
    newNode->next = NULL;

    if(*head == NULL){ // verifica se a lista está vazia
        *head = newNode;
    } else{
        struct node * nav;
        nav = *head;

        if(nav->task->burst > newNode->task->burst) // verifica se a task localizada na primeira posição da fila já não tem um tempo necessário de execução maior que a task a ser adicionada
        {
            newNode->next = nav;
            *head = newNode;
        } else{

            while (nav->next != NULL){ // percorre a lista até o final
                if(nav->next->task->burst > newNode->task->burst)// verifica se a task da próxima posição não tem um tempo necessário para execução maior que a nova task 
                {
                    newNode->next = nav->next;
                    break;
                }
                nav = nav->next;
            }
            nav->next = newNode;
        }
    }
}

// delete the selected task from the list
void delete(struct node **head, Task *task) {
    struct node *temp;
    struct node *prev;

    temp = *head;
    // special case - beginning of list
    if (strcmp(task->name,temp->task->name) == 0) {
        *head = (*head)->next;
    }
    else {
        // interior or last element in the list
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name,temp->task->name) != 0) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
    }
}

// traverse the list
void traverse(struct node *head) {
    struct node *temp;
    temp = head;

    while (temp != NULL) {
        printf("[%s] [%d] [%d]\n",temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}
