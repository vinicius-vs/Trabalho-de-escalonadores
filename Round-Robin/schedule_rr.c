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

    struct task *newTask = malloc(sizeof(struct task)); // criando uma nova tesk que irá receber os parâmetro
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = fila->lastId +
                   1; // é pego a variável responsável por guardar o último id alocado na fila é adicionado mais 1 para adiciona o id da nova task
    insert(&fila->fila, newTask);// chama a função para alocar a task criada na fila
    fila->lastId++;
}

// invoke the scheduler
void schedule(struct filaAptos *fila) {

    int c = 0;

    int time = 0; // variável utilizado para definir quanto tempo cada task irá utilizar
    struct node *nav; // variável utilizada para navegar na lista de tesks
    struct task *currentTask; // variável criada para gravar a tarefa atual

    while (1) {
        if (&fila->fila->task == NULL)
        {
            break;
        }
        currentTask = fila->fila->task; // pegando a task atual na fila
        time = currentTask->burst > quantum ? quantum : currentTask->burst; //caso o tempo necessário para executar a tesk seja maior que o limite de definido no QUANTUN e atributo o próprio QUANTUM na variável time caso ao contrário e definido o tempo necessário para a tesk

        run(currentTask, time); // executa a função run do processador
        currentTask->burst = currentTask->burst - time; // reduzindo o tempo necessário para realizar a tesk

        delete(&fila->fila, currentTask); // Deletar a task da posição atual
        if (currentTask->burst > 0) { //verificar a necessidade da task entrar novamente na fila
            insert(&fila->fila, currentTask); // inserindo novamente a task na fila
        }
    }
}
