#include <stdio.h>
#include <stdlib.h>
#include "structures/myProcess.h"
#include "structures/heap.h"
#include "utils/utils.h"
#include "algos/FCFS.h"
#include "algos/SJF.h"
#include "algos/RoundRobin.h"
#include "algos/SRTF.h"


int main(){
    int choice=0;
    while(choice!=-1){
        int numProcess, timeQuantum;
            printf("\n\n ************************************  Select Your Choice ****************************************");
            printf("\n 1.  Round Robin");
            printf("\n 2.  Shortest Job First");
            printf("\n 3.  FCFS ");
            printf("\n 4.  SRTF");
            printf("\n Enter your choice");
            scanf("%d",&choice);
            if(choice<1 || choice>5){
                    printf("\nPlease enter the correct algorithm.");
                    continue;
            }else if(choice>=1 && choice<=4){
                    printf("\nEnter the number of the process: ");
                    scanf("%d", &numProcess);
                    int arrivalTime[numProcess], burstTime[numProcess];

                    printf("\nEnter arrival time of the process: ");
                    for (int i = 0; i < numProcess; i++) scanf("%d", &arrivalTime[i]);

                    printf("\nEnter burst time of the process: ");
                    for (int i = 0; i < numProcess; i++) scanf("%d", &burstTime[i]);

                    if(choice==1){
                        printf("\nEnter time quantum:");
                        scanf("%d", &timeQuantum);
                        struct myProcess pr = createProcessPreEmptive(numProcess, arrivalTime, burstTime, timeQuantum);
                        roundRobin(&pr);
                        printProcessPreEmptive(&pr);
                    }else if(choice==2){
                        struct myProcess pr = createProcess(numProcess, arrivalTime, burstTime);
                        SJF(&pr);
                        printProcess(&pr);
                    }else if(choice==3){
                        struct myProcess pr = createProcess(numProcess, arrivalTime, burstTime);
                        FCFS(&pr);
                        printProcess(&pr);
                    }else if(choice==4){
                        struct myProcess pr = createProcess(numProcess, arrivalTime, burstTime);
                        SRTF(&pr);
                        printProcessPreEmptive(&pr);
                    }
            }else {
                printf("\nWrong Input, Exiting Program.");
                break;
            }
        printf("\n\nTo exit enter -1 or to continue enter 1: ");
        scanf("%d", &choice);
    }
}