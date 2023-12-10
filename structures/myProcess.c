//structures/myProcess.c
#include "../utils/utils.h"
#include "myProcess.h"

struct myProcess createProcess(int numProcess, int arrivalTime[], int burstTime[]) {
    struct myProcess newProcess; 

    newProcess.numProcess = numProcess;
    newProcess.idleCPUTime = 0;
    newProcess.timeSpent = 0;
    newProcess.totalWaitingTime = 0;
    newProcess.totalTurnAroundTime = 0;
    newProcess.contextSwitches = -1;
    newProcess.timeQuantum = -1;

    for (int i = 0; i < numProcess; i++) {
        newProcess.arrivalTime[i] = arrivalTime[i];
        newProcess.burstTime[i] = burstTime[i];
    }

    return newProcess;
}

struct myProcess createProcessPreEmptive(int numProcess, int arrivalTime[], int burstTime[],
                                         int timeQuantum) { // Creates a new instance of structure myProcess
    struct myProcess newProcess; // declare a instace of myProcess

    newProcess.numProcess = numProcess;
    newProcess.idleCPUTime = 0;
    newProcess.timeSpent = 0;
    newProcess.totalWaitingTime = 0;
    newProcess.totalTurnAroundTime = 0;
    newProcess.contextSwitches = 0;
    newProcess.timeQuantum = timeQuantum;

    for (int i = 0; i < numProcess; i++) {
        newProcess.arrivalTime[i] = arrivalTime[i];
        newProcess.burstTime[i] = burstTime[i];
    }

    return newProcess;
}

void printProcess(struct myProcess *pr) { 
    printf("\n");
    printf("\nTotal time spent on running these process(s): %d", pr->timeSpent);
    printf("\nTotal idle CPU time: %d", pr->idleCPUTime);
    printf("\n");

    printf("\nCompletion Time:     ");
    printArr(pr->completionTime, pr->numProcess);

    printf("\nWaiting Time:     ");
    printArr(pr->waitingTime, pr->numProcess);

    printf("\nTurn Around Time:    ");
    printArr(pr->turnAroundTime, pr->numProcess);

    printf("\n");
    printf("\nAverage Waiting Time: %.2f", (float) pr->totalWaitingTime / (float) pr->numProcess);
    printf("\nAverage Turn Around Time: %.2f", (float) pr->totalTurnAroundTime / (float) pr->numProcess);
}

void printProcessPreEmptive(struct myProcess *pr) { 
    printf("\n");
    printf("\nTotal time spent on running these process(s): %d", pr->timeSpent);
    printf("\nTotal idle CPU time: %d", pr->idleCPUTime);
    printf("\n");

    printf("\nCompletion Time:  ");
    printArr(pr->completionTime, pr->numProcess);

    printf("\nTurn Around Time: ");
    printArr(pr->turnAroundTime, pr->numProcess);

    printf("\nWaiting Time:  ");
    printArr(pr->waitingTime, pr->numProcess);

    printf("\nResponse Time:  ");
    printArr(pr->responseTime, pr->numProcess);

    printf("\n");
    printf("\nAvg Waiting Time: %.2f", (float) pr->totalWaitingTime / (float) pr->numProcess);
    printf("\nAvg Turn Around Time: %.2f", (float) pr->totalTurnAroundTime / (float) pr->numProcess);
    printf("\nNumber of context switches: %d", pr->contextSwitches);
}