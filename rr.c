#include <stdio.h>
#include <stdlib.h>

struct proc{
    int pid;
    int waiting_time;
    int tat;
    int arrival_time;
    int per_CBT;
    int remaining_time;
    struct proc* next;
    struct proc* prev;
};

int main(){
    int NOP, y, wt, tat, flag, quant, temp_var;
    int total_time = 0;
    float avg_tat = 0.0;
    float avg_wt = 0.0;

    printf("Enter the number of processes: ");
    scanf("%d", &NOP);
    y = NOP;
    struct proc* head = NULL;

    for(int i = 1; i<=NOP; i++){
        struct proc* temp = (struct proc*)malloc(sizeof(struct proc));
        temp->pid = i;
        printf("Enter the cycle burst: ");
        scanf("%d", &temp_var);
        temp->per_CBT = temp_var;
        temp->remaining_time = temp->per_CBT;

        printf("Enter the arrival time: ");
        scanf("%d", &temp_var);
        temp->arrival_time = temp_var;

        if (head == NULL){
            head=temp;
            temp->next = NULL;
            temp->prev = NULL;
        }
        else{
            struct proc* temp1 = head;
            while(temp1->next!=NULL){
                temp1 = temp1->next;
            }
            temp1->next = temp;
            temp->prev = temp1;
            temp->next = NULL;
        }
    }

    struct proc* temp1 = head;
    while(temp1->next!=NULL){
        temp1 = temp1->next;
    }

    temp1->next = head;
    head->prev = temp1;


    printf("Enter the time quantum: ");
    scanf("%d", &quant);

    struct proc* n = head;
    while(y!=0){
        if(n->remaining_time <= quant && n->remaining_time > 0){
            total_time += n->remaining_time;
            n->remaining_time = 0;
            flag = 1;
        }

        else if(n->remaining_time>quant && n->remaining_time > 0){
            n->remaining_time-=quant;
            total_time+=quant;
        }

        if(flag == 1 && n->remaining_time == 0){
            flag = 0;
            y--;
            n->waiting_time = total_time-n->per_CBT-n->arrival_time;
            printf("The process with id %d has completed with a waiting time of %d\n", n->pid, n->waiting_time);
            wt += n->waiting_time;
            tat += n->waiting_time + n->per_CBT;
        }
        if(n->next->arrival_time <= total_time){
            n = n->next;
        }
        else{
            n = head;
        }
    }
    printf("The average waiting time: %f", (wt*1.0)/(NOP*2));
    printf("The average turnaround time: %f", (tat*1.0)/(NOP*2));
}

