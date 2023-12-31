#include "../utils/utils.h"
#include "../structures/heap.h"
#include "SJF.h"

void SJF(struct myProcess *pr) {
    int numProcess = pr->numProcess;
    int timeSpent = 0;
    int *turnAroundTime = pr->turnAroundTime;
    int *completionTime = pr->completionTime;
    int *waitingTime = pr->waitingTime;
    int totalTurnAroundTime = 0;
    int totalWaitingTime = 0;
    int arrivalTime[numProcess];
    int burstTime[numProcess];


    for (int i=0; i<numProcess; i++) {
        arrivalTime[i] = pr->arrivalTime[i];
        burstTime[i] = pr->burstTime[i];
    }

    struct heap h = createHeap(); 

    int minIndex = findMinIndex(arrivalTime, numProcess);
    if (arrivalTime[minIndex] > timeSpent) {
        timeSpent += arrivalTime[minIndex] - timeSpent;
    }

    int completedProcess = 0; 
    while (completedProcess < numProcess) {
        minIndex = findMinIndex(arrivalTime, numProcess);
        if (arrivalTime[minIndex] > timeSpent && burstTime[minIndex] != 0) {
            timeSpent += arrivalTime[minIndex] - timeSpent;
        }
        for (int i = 0; i < numProcess; i++) {
            if (arrivalTime[i] <= timeSpent && burstTime[i] > 0 && arrivalTime[i] != -1) {
                insertHeap(&h, burstTime[i], i);
                burstTime[i] = 0; 
            }
        }

        if (h.length != 0) {
            int removedIndex = h.index[0];
            int removedBurstTime = h.que[0];
            deque(&h);
            int removedArrivalTime = arrivalTime[removedIndex];
            arrivalTime[removedIndex] = -1; 
            completedProcess++;
            timeSpent += removedBurstTime;
            completionTime[removedIndex] = timeSpent;
            turnAroundTime[removedIndex] = completionTime[removedIndex] - removedArrivalTime; // TAT = CT - AT
            waitingTime[removedIndex] = turnAroundTime[removedIndex] - removedBurstTime; 
        }
    }
    for (int i = 0; i < numProcess; i++) {
        totalTurnAroundTime += turnAroundTime[i];
        totalWaitingTime += waitingTime[i];
    }
    pr->timeSpent = timeSpent;
    pr->totalTurnAroundTime = totalTurnAroundTime;
    pr->totalWaitingTime = totalWaitingTime;
}