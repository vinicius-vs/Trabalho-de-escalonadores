#include "schedule_sjf.h"
#include "list.h"
#include "task.h"
#include "CPU.h"
#include <malloc.h>

// add a task to the list 
void add(char *name, int priority, int burst, struct filaAptos * fila){

    struct task * newTask = malloc(sizeof(struct task)); // criando uma nova tesk que irá receber os parâmetro
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = fila->lastId + 1; // é pego a variável responsável por guardar o último id alocado na fila é adicionado mais 1 para adiciona o id da nova task
    insert(&fila->fila, newTask);// chama a função para alocar a task criada na fila de forma ordenada usando o burst como parâmetro de ordenação
    fila->lastId++;
}

// invoke the scheduler
void schedule(struct filaAptos * fila){
   struct task * currentTask;

    while (1){
        if (&fila->fila->task == NULL){ // verifica se a lista está vazia.
            break;
        }
        currentTask = fila->fila->task; // pega a primeira task da fila
        run(currentTask, currentTask->burst); // executa a função run da biblioteca CPU.h
        delete(fila,currentTask); // deleta a task já executado da lista
    }
}
