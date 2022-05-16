#include "schedule_rr_FIFO.h"
#include "task.h"
#include "list.h"
#include <malloc.h>
#include "CPU.h"

void startLista( struct  FilaDePrioridade * fila){
    fila->lastId = 0;
    fila->filaPri = NULL;
}

// add a task to the list 
void add(char *name, int priority, int burst, struct FilaDePrioridade * fila){

    struct task * newTask = malloc(sizeof(struct task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = fila->lastId + 1;

    struct FilaDeAptos * nav;
    nav = fila->filaPri;

    if(fila->filaPri == NULL){ // verifica se a lista de prioridade esta vazia
        struct FilaDeAptos * newFilaDeAptos = malloc(sizeof(struct FilaDeAptos)); 
        newFilaDeAptos->prioridade = priority;
        insert(&newFilaDeAptos->filaAdp,newTask);
        fila->filaPri = newFilaDeAptos;
    }else if(fila->filaPri->prioridade > priority){
        struct FilaDeAptos * newFilaDeAptos = malloc(sizeof(struct  FilaDeAptos));
        newFilaDeAptos->prioridade = priority;
        insert(&newFilaDeAptos->filaAdp, newTask);
        newFilaDeAptos->nextFila = fila->filaPri;
        fila->filaPri = newFilaDeAptos;
    } else {
        while (1){
            if(nav->prioridade == priority){
                insert(&nav->filaAdp,newTask);
                break;
            } else if (nav->nextFila == 0){
                struct  FilaDeAptos * newFilaDeAptos = malloc(sizeof(struct FilaDeAptos));
                newFilaDeAptos->prioridade = priority;
                insert(&newFilaDeAptos->filaAdp,newTask);
                nav->nextFila= newFilaDeAptos;
                break;
            } else if(nav->nextFila->prioridade > priority){
                struct  FilaDeAptos * newFilaDeAptos = malloc(sizeof(struct FilaDeAptos));
                newFilaDeAptos->prioridade = priority;
                insert(&newFilaDeAptos->filaAdp, newTask);
                newFilaDeAptos->nextFila = nav->nextFila;
                nav->nextFila = newFilaDeAptos;
                break;
            }
            nav = nav->nextFila;
        }
    }
    fila->lastId++;
}

// invoke the scheduler
void schedule(struct  FilaDePrioridade * fila){
    int time = 0;
    struct task * currentTask;

    struct FilaDeAptos * navFilas;
    navFilas = fila->filaPri;

    while (1){
        if(navFilas == NULL){
            break;
        }
        while (1){
            if(&navFilas->filaAdp->task == NULL){
                break;
            }
            currentTask = navFilas->filaAdp->task;
            time = currentTask->burst > quantum ? quantum : currentTask->burst;
            run(currentTask,time);
            currentTask->burst = currentTask->burst - time;
            delete(&navFilas->filaAdp, currentTask);
            if (currentTask->burst > 0){
                insert(&navFilas->filaAdp,currentTask);
            }
        }
        navFilas = navFilas->nextFila;
    }
}
