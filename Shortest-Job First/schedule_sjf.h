#define MIN_PRIORITY 1
#define MAX_PRIORITY 10


// struct usada para armazenar o começo da fila.
struct filaAptos{
    struct node * fila;
    int lastId;
};

// add a task to the list 
void add(char *name, int priority, int burst, struct filaAptos * fila);

// invoke the scheduler
void schedule(struct  filaAptos * fila);
