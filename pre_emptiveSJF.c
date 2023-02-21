// preemptive SJF
#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100
#define TIME_QUANTUM 1

typedef struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int wait_time;
    int turnaround_time;
} process;

typedef struct queue_node {
    // a queue for the processes
    process *proc; 
    struct queue_node *next;
} queue_node;

typedef struct priority_queue {
    // this is for the SJF
    queue_node *head;
} priority_queue;

void enqueue(priority_queue *q, process *p, int priority) {
    queue_node *new_node = (queue_node*) malloc(sizeof(queue_node));
    new_node->proc = p;
    new_node->next = NULL;
    if (q->head == NULL || priority < q->head->proc->remaining_time) {
        // in case the first node of teh priority queue has higher cycles remaining then the new head is the new_node
        new_node->next = q->head;
        q->head = new_node;
    }
    else {
        // else we are seeing where to insert the new node
        queue_node *current = q->head;
        while (current->next != NULL && current->next->proc->remaining_time <= priority) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

process *dequeue(priority_queue *q) {
    if (q->head == NULL) {
        return NULL;
    }
    process *p = q->head->proc;
    queue_node *temp = q->head;
    q->head = q->head->next; //emptying the first node as it has the highest priority
    free(temp);
    return p;
}

int main() {
    int n, i, j;
    process *procs[MAX_PROCESSES];
    priority_queue ready_queue = {NULL};
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        // getting the properties of the processes
        procs[i] = (process*) malloc(sizeof(process));
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &procs[i]->arrival_time, &procs[i]->burst_time, &procs[i]->priority);
        procs[i]->pid = i + 1;
        procs[i]->remaining_time = procs[i]->burst_time;
        procs[i]->wait_time = 0;
        procs[i]->turnaround_time = 0;
        enqueue(&ready_queue, procs[i], procs[i]->remaining_time); //first entering all the processes on the basis of the remaining time
    }
    int current_time = 0;
    int num_completed = 0;
    float avg_tat = 0;
    float avg_waiting = 0;
    while (num_completed < n) {
        process *current_process = dequeue(&ready_queue);
        if (current_process == NULL) {
            current_time++;
            continue;
        }
        if (current_process->remaining_time == current_process->burst_time) {
            current_process->wait_time = current_time - current_process->arrival_time;
            if (current_process->wait_time<0){
                current_process->wait_time = 0;
            }
        }
        if (current_process->remaining_time <= TIME_QUANTUM) {
            current_time += current_process->remaining_time;
            current_process->remaining_time = 0;
            num_completed++;
            current_process->turnaround_time = current_time - current_process->arrival_time;
            printf("Process %d completed (Wait time = %d, Turnaround time = %d)\n", current_process->pid, current_process->wait_time, current_process->turnaround_time);
            avg_waiting += current_process->wait_time;
            avg_tat += current_process->turnaround_time;
        }
        else {
            current_time += TIME_QUANTUM;
            current_process->remaining_time -= TIME_QUANTUM;
            enqueue(&ready_queue, current_process, current_process->remaining_time);
        }

    }

    printf("%f %f are the average waiting time and turnaround time", avg_waiting/num_completed, avg_tat/num_completed);
}


/*
We first define a process struct, which contains details about each process such as arrival time, burst time, priority, remaining time, wait time, and turnaround time.

We also define a queue_node struct, which contains a pointer to a process and a pointer to the next node in the queue.

We then define a priority_queue struct, which contains a pointer to the head of the queue.

We define two functions for the priority queue: enqueue and dequeue. The enqueue function takes a process and a priority as arguments, and adds the process to the queue based on its priority. The dequeue function removes the process with the highest priority from the queue and returns it.

In the main function, we first get the number of processes and their details from the user, and create an array of process pointers to store them. We then add all the processes to the ready queue using the enqueue function.

We initialize the current_time variable to 0 and the num_completed variable to 0. The current_time variable is used to keep track of the current time, and the num_completed variable is used to keep track of the number of processes that have completed execution.

We enter a loop that continues until all processes have completed execution. In each iteration of the loop, we dequeue the process with the highest priority from the ready queue using the dequeue function.

If there are no processes in the ready queue, we increment the current_time variable and continue with the next iteration.

If the current process has just started execution, we calculate its wait time as the difference between the current time and the process's arrival time.

If the current process has remaining time less than or equal to the time quantum, we complete the process and calculate its turnaround time as the difference between the current time and the process's arrival time. We also increment the num_completed variable and print the process's details.

If the current process has remaining time greater than the time quantum, we decrement its remaining time by the time quantum and add it back to the ready queue using the enqueue function.

Finally, we repeat steps 7-11 until all processes have completed execution.
*/
