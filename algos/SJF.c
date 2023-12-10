#include "../utils/utils.h"
#include "../structures/heap.h"
#include "SJF.h"

void SJF(struct myProcess *pr) {
    int numProcess = pr->numProcess;
    int timeSpent = 0, idleCPUTime = 0;
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

    struct heap h1 = createHeap(); 

    int minIndex = findMinIndex(arrivalTime, numProcess);
    if (arrivalTime[minIndex] > timeSpent) {
        idleCPUTime += arrivalTime[minIndex] - timeSpent;
        timeSpent += arrivalTime[minIndex] - timeSpent;
    }

    int completedProcess = 0; 
    while (completedProcess < numProcess) {
        minIndex = findMinIndex(arrivalTime, numProcess);
        if (arrivalTime[minIndex] > timeSpent && burstTime[minIndex] != 0) {
            idleCPUTime += arrivalTime[minIndex] - timeSpent;
            timeSpent += arrivalTime[minIndex] - timeSpent;
        }
        for (int i = 0; i < numProcess; i++) {
            if (arrivalTime[i] <= timeSpent && burstTime[i] > 0 && arrivalTime[i] != -1) {
                insertHeap(&h1, burstTime[i], i);
                burstTime[i] = 0; 
            }
        }

        if (h1.length != 0) {
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
    // Updating the original data in the sturct
    pr->timeSpent = timeSpent;
    pr->idleCPUTime = idleCPUTime;
    pr->totalTurnAroundTime = totalTurnAroundTime;
    pr->totalWaitingTime = totalWaitingTime;
}