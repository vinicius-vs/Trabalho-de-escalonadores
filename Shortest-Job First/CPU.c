/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>
#include <unistd.h>
#include "task.h"

// run this task for the specified time slice
void run(Task *task, int slice) {
    printf("Running task = [%s] [%d] [%d] for %d units.\n",task->name, task->priority, task->burst, slice);
    sleep(slice/60); // espera o tempo da execução da task
}
