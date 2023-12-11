#include "../utils/utils.h"
#include "../structures/heap.h"
#include "SRTF.h"

void SRTF(struct myProcess *pr) {
    int numProcess = pr->numProcess;
    int timeSpent = 0;
    int idleCPUTime = 0;
    int  totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    int contextSwitches = 0;
    int *turnAroundTime = pr->turnAroundTime;
    int *completionTime = pr->completionTime;
    int *waitingTime = pr->waitingTime;
    int timeQuantum = pr->timeQuantum;
    int arrivalTime[numProcess], remainingBurstTime[numProcess];

    for (int i = 0; i < numProcess; i++) {
        arrivalTime[i] = pr->arrivalTime[i];
        remainingBurstTime[i] = pr->burstTime[i];
    }

    struct heap h = createHeap();

    int completedProcess = 0; 
    int currentProcess = -1; 

    while (completedProcess < numProcess) {

        int minArrivalTimeIndex = findMinArrivalTimeIndex(arrivalTime, numProcess, timeSpent);
        if (minArrivalTimeIndex != -1) {
            insertHeap(&h, remainingBurstTime[minArrivalTimeIndex], minArrivalTimeIndex);
            arrivalTime[minArrivalTimeIndex] = -1;
        }


        if (currentProcess == -1) { 
            if (h.length != 0) {
                currentProcess = deque(&h); 
                contextSwitches++;
                if (remainingBurstTime[currentProcess] == pr->burstTime[currentProcess])
                    pr->responseTime[currentProcess] = timeSpent - pr->arrivalTime[currentProcess];

            } else { 
                timeSpent++;
                idleCPUTime++;
            }
        } else { 

            if (remainingBurstTime[currentProcess] == 0) { 
                completedProcess++;
                completionTime[currentProcess] = timeSpent;
                turnAroundTime[currentProcess] =
                        completionTime[currentProcess] - pr->arrivalTime[currentProcess];
                waitingTime[currentProcess] =
                        turnAroundTime[currentProcess] - pr->burstTime[currentProcess]; 
                currentProcess = -1;
            } else if (h.length != 0 && remainingBurstTime[currentProcess] > h.que[0]) {
                insertHeap(&h, remainingBurstTime[currentProcess], currentProcess);
                currentProcess = deque(&h);
                if (remainingBurstTime[currentProcess] == pr->burstTime[currentProcess])
                    pr->responseTime[currentProcess] = timeSpent - pr->arrivalTime[currentProcess];
                contextSwitches++;
            } else { 
                timeSpent++;
                remainingBurstTime[currentProcess]--;
            }
        }

    }

    for (int i = 0; i < numProcess; i++) {
        totalTurnAroundTime += turnAroundTime[i];
        totalWaitingTime += waitingTime[i];
    }

    pr->timeSpent = timeSpent;
    pr->idleCPUTime = idleCPUTime;
    pr->contextSwitches = contextSwitches - 1; 
    pr->totalTurnAroundTime = totalTurnAroundTime;
    pr->totalWaitingTime = totalWaitingTime;
}