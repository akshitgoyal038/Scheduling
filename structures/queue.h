#ifndef QUEUE_H
#define QUEUE_H

struct queue{
    int que[100];
    int index[100]; 
    int length; 
};

struct queue createQueue();

void insertQueueQue(struct queue *q, int index);

int dequeQue(struct queue *q);

void printQueue(struct queue *q);

int peekFrontQue(struct queue *q);

#endif