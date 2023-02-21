// simple FCFS

#include <stdio.h>
#include <stdlib.h>

struct proc{
    int arrival_time;
    int waiting_time;
    int tat;
    int cycle_burst;
    struct proc *next;
};

struct proc* head = NULL;

void enqueue(struct proc* new_proc){
    if (head==NULL){
        head = new_proc;
        head->next = NULL;
    }
    
    else{
        struct proc* temp = head;
        while(temp->next != NULL && temp->next->arrival_time <= new_proc->arrival_time){
            temp=temp->next;
        }
        new_proc->next = temp->next;
        temp->next = new_proc;
    }
}



int main(){
    int n;
    printf("enter the number of processes: ");
    scanf("%d", &n);
    
    for(int i = 0; i<n; i++){
        struct proc* temp = (struct proc*)malloc(sizeof(struct proc));
        printf("Enter the arrival time: ");
        scanf("%d", &temp->arrival_time);
        printf("Enter the cycle burst: ");
        scanf("%d", &temp->cycle_burst);
        
        enqueue(temp);
    }
    
    struct proc* temp1 = head;
    int ct = 0;
    while(temp1!=NULL){
        if(ct == temp1->arrival_time || ct>temp1->arrival_time){
            temp1->waiting_time = ct-temp1->arrival_time;
            ct+=temp1->cycle_burst;
            temp1->tat = ct - temp1->arrival_time;
            temp1 = temp1->next;
        }
        else{
            printf("ct invalid");
        }
    }
    
    temp1 = head;
    float total_tat = 0.0;
    float total_avg = 0.0;
    while(temp1!=NULL){
        total_avg += temp1->waiting_time;
        total_tat += temp1->tat;
        printf("%d %d\n", temp1->waiting_time, temp1->tat);
        temp1=temp1->next;
    }
    
    printf("averages: %f %f", total_tat/n, total_avg/n);
    
}
