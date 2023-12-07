#include "../structures/Process.h"
#include "../utils/utils.h"
#include "FCFS.h"

void FCFS(struct myProcess *pr) {
    // Destructring all the data from the process struct.
    int numProcess = pr->numProcess;
    int currentTime = 0, idleCPUTime = 0;
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

    int completed=0;
    while(completed!=numProcess){
        int minIndex=findMinIndex(arrivalTime, numProcess);
        if(arrivalTime[minIndex]>currentTime){
            currentTime += arrivalTime[minIndex] - currentTime;
        }
        currentTime+=burstTime[minIndex];
        turnAroundTime[minIndex] = currentTime - arrivalTime[minIndex];
        waitingTime[minIndex] = turnAroundTime[minIndex] - burstTime[minIndex];
        arrivalTime[minIndex] = -1; 
        completed+=1;
    }

    for (int i = 0; i < numProcess; i++) {
        totalTurnAroundTime += turnAroundTime[i];
        totalWaitingTime += waitingTime[i];
    }


    pr->currentTime= currentTime;
    pr->totalTurnAroundTime = totalTurnAroundTime;
    pr->totalWaitingTime = totalWaitingTime;
}