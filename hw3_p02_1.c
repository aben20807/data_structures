#include <stdio.h>

#define MAX_SIZE 4
typedef struct{
    char data;
}element;
element nc_queue[MAX_SIZE];
int rear = -1;
int front = -1;

void initQ();
void addQ(char);
element deleteQ();
void qFull();
void qEmpty();
void move();

int main(){
    initQ();
    int mode;
    while(1){
        printf("Insert(1)delete(2):");
        scanf("%d", &mode);
        getchar();
        if(mode == -1){
            break;
        }
        else if(mode == 1){
            char num;
            printf("Insert number:");
            scanf("%c", &num);
            addQ(num);
        }
        else if(mode == 2){
            deleteQ();
        }
        else{
            printf("error mode\n");
            continue;
        }
        printf("Front=%d,Rear=%d\n", front, rear);
        printf("Queue:[%c][%c][%c][%c]\n", nc_queue[0].data, nc_queue[1].data, nc_queue[2].data, nc_queue[3].data);
    }
    return 0;
}

void initQ(){
    int i;
    for (i = 0; i < MAX_SIZE; i++){
        nc_queue[i].data = ' ';
    }
}

void addQ(char num){
    if(rear == MAX_SIZE-1 && front != -1){
        move();
        nc_queue[++rear].data = num;
    }
    else if(rear == MAX_SIZE-1){
        qFull();
    }
    else{
        nc_queue[++rear].data = num;
    }
}

element deleteQ(){
    if(front == rear){
        qEmpty();
        return nc_queue[front];
    }
    nc_queue[front+1].data = ' ';
    return nc_queue[++front];
}
void qFull(){
    printf("Queue is full\n");
    return;
}

void qEmpty(){
    printf("Queue is empty\n");
    return;
}

void move(){
    int i;
    for(i = 0; i < MAX_SIZE-front-1; i++){
        nc_queue[i] = nc_queue[front+i+1];
    }
    for(i; i < MAX_SIZE; i++){
        nc_queue[i].data = ' ';
    }
    rear -= (front+1);
    front -= (front+1);
    return;
}
