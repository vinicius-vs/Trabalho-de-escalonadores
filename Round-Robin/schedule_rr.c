#include "schedule_rr.h"
#include "list.h"
#include "task.h"
#include "CPU.h"
#include <stdio.h>
#include <malloc.h>


void startFilaAptos(struct filaAptos *fila) {
    fila->lastId = 0;
    fila->fila = 0;
}

// add a task to the list 
void add(char *name, int priority, int burst, struct filaAptos *fila) {

    struct task *newTask = malloc(sizeof(struct task)); // criando uma nova task que irá receber os parâmetros
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = fila->lastId +
                   1; // pega a variável responsável por guardar o último id alocado na fila, e adicionado mais 1 para adicionar o id da nova task
    insert(&fila->fila, newTask);// chama a função para alocar a task criada na fila
    fila->lastId++;
}

// invoke the scheduler
void schedule(struct filaAptos *fila) {

    int c = 0;

    int time = 0; // variável usada para definir quanto tempo cada task irá gastar
    struct node *nav; // variável utilizada para navegar na lista de tasks
    struct task *currentTask; // variável criada para gravar a tarefa atual

    while (1) {
        if (&fila->fila->task == NULL)
        {
            break;
        }
        currentTask = fila->fila->task; // pega a task atual na fila
        time = currentTask->burst > quantum ? quantum
                                            : currentTask->burst; //caso o tempo necessário para executar a task seja maior que o limite é definido no QUANTUN e atributo o próprio QUANTUM na variável time, caso o contrário é definido o tempo necessário para a task

        run(currentTask, time); // executa a função run do processador
        currentTask->burst = currentTask->burst - time; // reduz o tempo necessário para realização da task

        delete(&fila->fila, currentTask); // Deleta a task da posição atual
        if (currentTask->burst > 0) { //verifica a necessidade da task, entra novamente na fila
            insert(&fila->fila, currentTask); // inserindo novamente a task na fila
        }
    }
}
