#include "../structures/myProcess.h"
#include "../utils/utils.h"
#include "FCFS.h"

void FCFS(struct myProcess *pr) {
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

    while (findMinIndex(arrivalTime, numProcess) != -1) {
        int minIndex = findMinIndex(arrivalTime, numProcess);

        if (arrivalTime[minIndex] == timeSpent);
        else if (arrivalTime[minIndex] < timeSpent); 
        else if (arrivalTime[minIndex] > timeSpent) { 
            timeSpent += arrivalTime[minIndex] - timeSpent;
        }

        timeSpent += burstTime[minIndex];
        turnAroundTime[minIndex] = timeSpent - arrivalTime[minIndex];
        completionTime[minIndex] = timeSpent;
        waitingTime[minIndex] = turnAroundTime[minIndex] - burstTime[minIndex]; 

        arrivalTime[minIndex] = -1; 
    }

    for (int i = 0; i < numProcess; i++) {
        totalTurnAroundTime += turnAroundTime[i];
        totalWaitingTime += waitingTime[i];
    }
    pr->timeSpent = timeSpent;
    pr->totalTurnAroundTime = totalTurnAroundTime;
    pr->totalWaitingTime = totalWaitingTime;
}