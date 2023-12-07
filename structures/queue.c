#include <stdio.h>

struct queue createQueue(){
    struct queue newinstance;
    newinstance.length=0;
    return newinstance;
}

void insertQueue(struct queue *q,int index){
    if(q->length<50){
        q->index[q->length]=index;
        q->length++;
    }else{
        printf("\n Queue Size is FULL\n");
        return;
    }
}

int deque(struct queue *q){
    if(q->length==0) return -1;
    int element=q->index[0];
    for(int i=0;i<q->length;i++){
        q->que[i]=q->que[i+1];
        q->index[i]=q->index[i+1];
    }
    q->length-=1;
    return element;
}

int peek(struct queue *q){
    if(q->length>=0) return q->que[0];
}

void printQueue(stuct queue *q){
    printf("\nElements:");
    for (int i = 0; i < q->length; i++) printf("%d ", q->que[i]);
    printf("\nIndexes: ");
    for (int i = 0; i < q->length; i++) printf("%d ", q->index[i]);
}