#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

static int quantum = 60;

struct FilaDeAptos{
    struct node * filaAdp;
    int prioridade;
    struct FilaDeAptos * nextFila;
};

struct FilaDePrioridade{

    struct FilaDeAptos * filaPri;
    int lastId;

};


void startLista( struct  FilaDePrioridade * fila);

// add a task to the list 
void add(char *name, int priority, int burst, struct FilaDePrioridade * fila);

// invoke the scheduler
void schedule(struct  FilaDePrioridade * fila);
