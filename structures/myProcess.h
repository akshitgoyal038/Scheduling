// structures/myProcess.h
#ifndef MY_PROCESS_H
#define MY_PROCESS_H

struct myProcess { 
    int numProcess; 
    int idleCPUTime;
    int timeSpent; 
    int totalTurnAroundTime;
    int totalWaitingTime;
    int arrivalTime[100];
    int burstTime[100];
    int completionTime[100]; 
    int turnAroundTime[100]; 
    int waitingTime[100];

    int timeQuantum; 
    int contextSwitches; 
    int responseTime[100];
};

struct myProcess createProcess(int numProcess, int arrivalTime[], int burstTime[]);

struct myProcess createProcessPreEmptive(int numProcess, int arrivalTime[], int burstTime[], int timeQuantum);

void printProcess(struct myProcess *pr);

void printProcessPreEmptive(struct myProcess *pr);

#endif