#include <stdio.h>

#define MAX_SIZE 4
typedef struct{
    char data;
}element;
element c_queue[MAX_SIZE];
int rear = 0;
int front = 0;

void initQ();
void addQ(char);
element deleteQ();
void qFull();
void qEmpty();
int isEmpty();
int isFull();

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
        printf("Queue:[%c][%c][%c][%c]\n", c_queue[0].data, c_queue[1].data, c_queue[2].data, c_queue[3].data);
    }
    return 0;
}

void initQ(){
    int i;
    for (i = 0; i < MAX_SIZE; i++){
        c_queue[i].data = ' ';
    }
}

void addQ(char num){
    if(front == rear && isFull()){
        qFull();
    }
    else{
        c_queue[rear].data = num;
        rear = (rear + 1) % (MAX_SIZE);
    }
}

element deleteQ(){
    if(front == rear && isEmpty()){
        qEmpty();
        return c_queue[front];
    }
    else{
        c_queue[front].data = ' ';
        front = (front + 1) % (MAX_SIZE);
        return c_queue[front];
    }
}
void qFull(){
    printf("Queue is full\n");
    return;
}

void qEmpty(){
    printf("Queue is empty\n");
    return;
}

int isEmpty(){//check if empty
    int i;
    int is = 1;
    for(i = 0; i < MAX_SIZE; i++){
        if(c_queue[i].data != ' ')
            is = 0;
    }
    return is;
}

int isFull(){//check if full
    int i;
    int is = 1;
    for(i = 0; i < MAX_SIZE; i++){
        if(c_queue[i].data == ' ')
            is = 0;
    }
    return is;
}
