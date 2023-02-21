//Priority pre emptive

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

//  printing the gantt chart not required
/*
void print_table(struct process *p) {
    printf("\n\nProcess ID\tArrival Time\tBurst Time\tPriority\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority);
    }
    printf("\n\n");
}
*/


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
        input(&p[i]); 
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

        p[min_priority_index].remaining_time--; //running one cycle so decrementing it
        time++; //incrementing the total time cycle

        printf(" P%d %d", p[min_priority_index].pid, time); //printing the gantt_chart

        if (p[min_priority_index].remaining_time == 0) { 
            int turnaround_time = time - p[min_priority_index].arrival_time; 
            int waiting_time = turnaround_time - p[min_priority_index].burst_time; 

            total_turnaround_time += turnaround_time; 
            total_waiting_time += waiting_time;
        }
    }

    printf("\n\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_turnaround_time / n);
}
