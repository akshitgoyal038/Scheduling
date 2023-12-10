#ifndef QUEUE_H
#define QUEUE_H

struct queue{
    int que[100]; // This will contain the main array
    int index[100]; // This will contain the index of element in the original data.
    int length; // Size of the queue
};

struct queue createQueue();
void insertQueue(struct queue *q, int index);

int deque(struct queue *q);

void printQueue(struct queue *q);

int peek(struct queue *q);

#endif