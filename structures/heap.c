#include <stdio.h>
#include "heap.h"

struct heap createHeap() { 
    struct heap newHeap;
    newHeap.min = __INT_MAX__;
    newHeap.length = 0;
    return newHeap;
}

void insertHeap(struct heap *h1, int element, int index) { 
    h1->que[h1->length] = element;
    h1->index[h1->length] = index;
    h1->length++;
    if (element < h1->min) {
        int previousMin = h1->que[0];
        int previousMinIndex = h1->index[0];
        h1->min = element;
        h1->que[0] = element;
        h1->index[0] = index;
        h1->que[h->length - 1] = previousMin;
        h1->index[h->length - 1] = previousMinIndex;
    }
}

int minInHeapIndex(struct heap *h) { 
    if (h->length == 0) return -1; 
    int minIndex = 0; 
    for (int i = 0; i < h->length; i++) {
        if (h->que[i] < h->que[minIndex] && h->que[i] != -1) minIndex = i;
        if (h->que[i] == h->que[minIndex] && h->que[i] != -1 && h->index[minIndex] > h->index[i]) minIndex = i;
    }
    h->min = h->que[minIndex];
    return minIndex;
}

int deque(struct heap *h) {
    if (h->length == 0) return -1;

    int removed = h->que[0];
    int removedIndex = h->index[0];
    for (int i = 0; i < h->length - 1; i++) {
        h->que[i] = h->que[i + 1];
        h->index[i] = h->index[i + 1];
    }
    int minIndex = minInHeapIndex(h);
    int indexOfMinIndex = h->index[minIndex];

    h->min = h->que[minIndex];
    h->que[minIndex] = h->que[0];
    h->index[minIndex] = h->index[0];

    h->que[0] = h->min;
    h->index[0] = indexOfMinIndex;
    h->length--;

    if (h->length == 0) h->min = __INT_MAX__; 

    return removedIndex;
}

void printHeap(struct heap *h1) { 
    printf("\nElements: ");
    for (int i = 0; i < h1->length; i++) printf("%d ", h1->que[i]);
}

int peekFront(struct heap *h1) { 
    return h1->que[0];
}