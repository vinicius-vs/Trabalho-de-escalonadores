/**
 * list data structure containing the tasks in the system
 */
#ifndef List_H
#define List_H


#include "task.h"

struct node {
    Task * task;
    struct node *next;
};

// insert and delete operations.
void insert(struct node **head, Task *task);
void delete(struct node **head, Task *task);
void traverse(struct node *head);


#endif //List_H