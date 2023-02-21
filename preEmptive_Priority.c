#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESS 10

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
};

int n; // Number of processes

void input(struct process *p) {
    // assigning the values 
    printf("Enter process details:\n");
    printf("PID: ");
    scanf("%d", &p->pid);
    printf("Arrival Time: ");
    scanf("%d", &p->arrival_time);
    printf("Burst Time: ");
    scanf("%d", &p->burst_time);
    printf("Priority: ");
    scanf("%d", &p->priority);
    p->remaining_time = p->burst_time;
}

//  printing the gauntt chart not required
/*
void print_table(struct process *p) {
    printf("\n\nProcess ID\tArrival Time\tBurst Time\tPriority\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority);
    }
    printf("\n\n");
}
*/

// this is a simple swapping 2 elements
void swap(struct process *p1, struct process *p2) {
    struct process temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}


void sort(struct process *p) {
    // bubble sorting the processes on the basis of the priorities
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].priority > p[j].priority) {
                swap(&p[i], &p[j]);
            }
        }
    }
}

int main() {

    struct process p[MAX_PROCESS]; // declaring an array of structures

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        input(&p[i]); //getting the properties of processes from the user
    }

    //print_table(p);

    sort(p); //bubble sorting

    int time = 0; // Current Time
    int total_waiting_time = 0; // Total Waiting Time
    int total_turnaround_time = 0; // Total Turnaround Time

    printf("\n\nGantt Chart:\n");
    //printf("0");

    while (1) {
        int i;
        for (i = 0; i < n; i++) {
            //getting the process which has come first(which is whose arrival time first matches with the current time)
            if (p[i].remaining_time > 0 && p[i].arrival_time <= time) {
                break;
            }
        }

        if (i == n) {
            // in case all the processes are reached then break the while loop
            break;
        }

        int min_priority = 999999; // this is the least priority value
        int min_priority_index;

        for (int j = i; j < n; j++) {
            if (p[j].remaining_time > 0 && p[j].arrival_time <= time && p[j].priority < min_priority) {
                // currently taking the exising process in the current cycle's priority and index as the benchmark, if there are older pre-empted function with higher priorities, then they are ignores as there is a new process with higher priority
                // the reason we are putting for loop is that to double check if there are any other process after element is having higher priority (coz look for i we are cecking only if there are cycles present and if it has arrived, not the priority)
                // we are checking if the process still has cycles, if it has already arrived, and if teh priority is higher than the exising one
                min_priority = p[j].priority;
                min_priority_index = j;
            }
        }

        p[min_priority_index].remaining_time--; //running one cycle so decrementing it
        time++; //incrementing the total time cycle

        printf(" P%d %d", p[min_priority_index].pid, time); //printing the gantt_chart

        if (p[min_priority_index].remaining_time == 0) { //in case the process is finished
            int turnaround_time = time - p[min_priority_index].arrival_time; //getting teh turnaround time for teh process
            int waiting_time = turnaround_time - p[min_priority_index].burst_time; //getting teh waiting time for teh process

            total_turnaround_time += turnaround_time; //getting the total of 2 values
            total_waiting_time += waiting_time;
        }
    }

    printf("\n\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_turnaround_time / n);
}


/*
Explanantion:

The algorithm schedules the processes based on their priorities. A process with a higher priority gets executed first, and if multiple processes have the same priority, then the process that arrived first gets executed first. The algorithm is preemptive, which means that if a new process with a higher priority arrives, the currently executing process will be preempted and the higher priority process will be executed.

Let's look at the code step by step:

We define a structure 'process' to store the details of each process such as Process ID (pid), Arrival Time, Burst Time, Priority, and Remaining Time.

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
};

We take the input for the number of processes and the details of each process from the user.
We then sort the processes based on their priority using the 'sort' function. The function uses a simple bubble sort algorithm to sort the processes in ascending order of their priority.

void sort(struct process *p) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].priority > p[j].priority) {
                swap(&p[i], &p[j]);
            }
        }
    }
}
We then use a while loop to execute the processes. Inside the loop, we first check for the process with the highest priority and execute it. If a new process with higher priority arrives, the currently executing process is preempted, and the new process gets executed. We keep track of the total waiting time and the total turnaround time of each process.

while (1) {
        int i;
        for (i = 0; i < n; i++) {
            if (p[i].remaining_time > 0 && p[i].arrival_time <= time) {
                break;
            }
        }

        if (i == n) {
            break;
        }

        int min_priority = 999999;
        int min_priority_index;

        for (int j = i; j < n; j++) {
            if (p[j].remaining_time > 0 && p[j].arrival_time <= time && p[j].priority < min_priority) {
                min_priority = p[j].priority;
                min_priority_index = j;
            }
        }

        p[min_priority_index].remaining_time--;
        time++;

        printf(" P%d %d", p[min_priority_index].pid, time);

        if (p[min_priority_index].remaining_time == 0) {
            int turnaround_time = time - p[min_priority_index].arrival_time;
            int waiting_time = turnaround_time - p[min_priority_index].burst_time;

            total_turnaround_time += turnaround_time;
            total_waiting_time += waiting_time;
        }
    }
Finally, we print the average waiting time and the average turnaround time of all the processes.

printf("\n\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_turnaround_time / n);
I hope this helps!





*/
