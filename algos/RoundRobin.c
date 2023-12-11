#include "../utils/utils.h"
#include "../structures/queue.h"
#include "RoundRobin.h"

void roundRobin(struct myProcess *pr) {
    int numProcess = pr->numProcess;
    int *turnAroundTime = pr->turnAroundTime;
    int *completionTime = pr->completionTime;
    int *waitingTime = pr->waitingTime;
    int timeQuantum = pr->timeQuantum;

    int timeSpent = 0, totalWaitingTime = 0, totalTurnAroundTime = 0;

    int arrivalTime[numProcess], remainingBurstTime[numProcess];

    for (int i = 0; i < numProcess; i++) {
        arrivalTime[i] = pr->arrivalTime[i];
        remainingBurstTime[i] = pr->burstTime[i];
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
                if (remainingBurstTime[currentProcess] == pr->burstTime[currentProcess]) pr->responseTime[currentProcess] = timeSpent - pr->arrivalTime[currentProcess];

                quantumCounter = 0; 
            } else { 
                timeSpent++;
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
    pr->totalTurnAroundTime = totalTurnAroundTime;
    pr->totalWaitingTime = totalWaitingTime;
}