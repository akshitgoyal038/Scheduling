#include <stdio.h>
#include "utils.h"

void printArr(int arr[], int length){ 
    for (int i=0; i<length; i++){
        printf("%d ", arr[i]);
    }
}

int findMinIndex(int arr[], int length){ 
    int min = __INT_MAX__, index = length;

    for (int i=0; i<length; i++) if (min > arr[i] && arr[i] != -1) {
        min = arr[i];
        index = i;
    }
    if (index == length) return -1;             
    
    return index;
}

int findMinArrivalTimeIndex(int arrivalTime[], int numProcess, int currentTime){ 
    int minIndex = -1;
    int minArrivalTime = __INT_MAX__;

    for (int i = 0; i < numProcess; i++) {
        if (arrivalTime[i] <= currentTime && arrivalTime[i] != -1) {
            if (arrivalTime[i] < minArrivalTime) {
                minArrivalTime = arrivalTime[i];
                minIndex = i;
            }
        }
    }

    return minIndex;
}