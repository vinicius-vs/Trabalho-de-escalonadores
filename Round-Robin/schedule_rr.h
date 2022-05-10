#ifndef Schedule_H
#define Schedule_H

#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

static int quantum = 90;

#include "list.h"

struct filaAptos{
    struct node * fila;
    int lastId;
};

void startFilaAptos(struct filaAptos * fila);

// add a task to the list
void add(char *name, int priority, int burst,struct filaAptos * fila);

// invoke the scheduler
void schedule(struct filaAptos * fila);

#endif //Schedule_H