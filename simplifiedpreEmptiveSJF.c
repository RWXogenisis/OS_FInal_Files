#include <stdio.h>
#include <stdlib.h>

struct proc{
    int pid;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int wait_time;
    int tat;
    struct proc* next;
};

struct proc* head = NULL;
int quant = 1;

void enqueue(struct proc* temp, int priority){
    if (head == NULL || head->remaining_time >priority){
        temp->next = head;
        head = temp;
    }
    else{
        struct proc* temp1 = head;
        while(temp1->next!=NULL && temp1->next->remaining_time<priority){
            temp1=temp1->next;
        }
        temp->next = temp1->next;
        temp1->next = temp;
    }
}

int main(int argc, char const *argv[])
{
    int n;
    printf("Enter the number of processes");
    scanf("%d", &n);

    for(int i = 0; i<n; i++){
        struct proc* temp = (struct proc*)malloc(sizeof(struct proc));
        printf("Enter the arrival time: ");
        scanf("%d", &temp->arrival_time);
        printf("Enter the burst time: ");
        scanf("%d", &temp->burst_time);
        temp->remaining_time = temp->burst_time;

        temp->pid = i+1;
        enqueue(temp, temp->remaining_time);
    }

    int total_time = 0;
    float avg_waiting = 0.0;
    float avg_tat = 0.0;
    int y = 0;

    while(y<n){
        struct proc* current = head;
        head = head->next;
        if(current == NULL){
            total_time++;
            continue;
        }

        if(current->burst_time == current->remaining_time){
            current->wait_time = total_time-current->arrival_time;
            if(current->wait_time < 0){
                current->wait_time = 0;
            }
        }

        if(current->remaining_time <= quant){
            total_time+=current->remaining_time;
            current->remaining_time = 0;
            y++;
            current->tat = total_time-current->arrival_time;

            printf("the process %d has completed wait time: %d tat: %d\n", current->pid, current->wait_time, current->tat);
            avg_tat+=current->tat;
            avg_waiting+=current->wait_time;
        }

        else{
            total_time+=quant;
            current->remaining_time-=quant;
            enqueue(current, current->remaining_time);
        }

    }
    printf("the averages: %f %f", avg_tat/y, avg_waiting/y);
}
