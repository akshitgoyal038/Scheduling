#include "../utils/utils.h"
#include "../structures/queue.h"
#include "RoundRobin.h"

void roundRobin(struct myProcess *pr) {
    int timeSpent = 0;
    int totalWaitingTime = 0;
    int numProcess = pr->numProcess;
    int idleCPUTime = 0;
    int totalTurnAroundTime = 0;
    int *turnAroundTime = pr->turnAroundTime;
    int *completionTime = pr->completionTime;
    int *waitingTime = pr->waitingTime;
    int timeQuantum = pr->timeQuantum;
    int contextSwitches = 0;
    int arrivalTime[numProcess];
    int remainingBurstTime[numProcess];



    for (int i = 0; i < numProcess; i++) {
        remainingBurstTime[i] = pr->burstTime[i];
        arrivalTime[i] = pr->arrivalTime[i];
    }

    struct queue q = createQueue();

    int completedProcess = 0; 
    int currentProcess = -1;
    int quantumCounter = 0; 



    while (completedProcess < numProcess) { 

        int minArrivalTimeIndex = findMinArrivalTimeIndex(arrivalTime, numProcess, timeSpent);

        if (minArrivalTimeIndex != -1) {
            insertQueueQue(&q, minArrivalTimeIndex);
            arrivalTime[minArrivalTimeIndex] = -1;
        }


        if (currentProcess == -1) { 
            if (q.length != 0) {
                currentProcess = dequeQue(&q); 
                contextSwitches++;
                if (remainingBurstTime[currentProcess] == pr->burstTime[currentProcess]) pr->responseTime[currentProcess] = timeSpent - pr->arrivalTime[currentProcess];

                quantumCounter = 0;
            } else { 
                timeSpent++;
                idleCPUTime++;
            }
        } else {
            if (quantumCounter < timeQuantum) remainingBurstTime[currentProcess]--; 

            if (remainingBurstTime[currentProcess] == 0) { 
                completedProcess++;
                timeSpent++;
                completionTime[currentProcess] = timeSpent;
                turnAroundTime[currentProcess] = completionTime[currentProcess] - pr->arrivalTime[currentProcess];
                waitingTime[currentProcess] = turnAroundTime[currentProcess] - pr->burstTime[currentProcess];
                currentProcess = -1;
                quantumCounter = 0;
            } else if (quantumCounter >= timeQuantum) { 
                insertQueueQue(&q, currentProcess); 
                currentProcess = -1;
                quantumCounter = 0;
            } else { 
                timeSpent++;
                quantumCounter++;
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