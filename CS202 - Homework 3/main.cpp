#include <iostream>
#include <fstream>
#include "string.h"
#include "PriorityQueue.h"
using namespace std;

/*
 * Title: Heaps, Priority Queues
 * Author: Alperen CAN 
 * ID: 21601740
 * Section: 1
 * Assignment: 3
 * Description: Computer Count Optimization for Max Av Time
*/
void calculateNextAvailableComputer(int *compReqFinishTime, const int computerCount, int &nextComputer, int &computerTime){
    int minTime = 2147483647; //INTEGER_MAX
    for(int i = 0; i < computerCount; i++){
        //if process is already finished for this computer,
        //take this one as available computer
        if(compReqFinishTime[i] <= computerTime){
            nextComputer = i;
            return;
        }else if(compReqFinishTime[i] < minTime){
            nextComputer = i;
            minTime = compReqFinishTime[i];
        }
    }

    //Take the computer with smallest finish time as available computer 
    //And make computer time equal to its finish time
    computerTime = minTime;
}

float calculateAverageWaitingTime(PriorityQueue pq, PQItemType *requests, const int reqCount, int computerCount, bool printResults){
    //first available computer for any request 
    int availableComputer = 0;
    //process finish time for computers
    int *compReqFinishTime = new int[computerCount];
    //time passed 
    int computerTime = 0;
    //request index
    int index = 0;
    //next request to insert to heap 
    PQItemType request = requests[0];
    float totalWaitingTime = 0;

    //initialize process finish time for computers
    for(int i = 0; i < computerCount; i++){
        compReqFinishTime[i] = -1;
    }

    //if all requests are not added to heap or heap is not empty, continue
    while(index < reqCount || !pq.pqIsEmpty()){
        //find requests that have smaller request time than computer time
        //add them into pq
        while(request.getRequestTime() <= computerTime && index < reqCount){
            pq.pqInsert(request);
            index++;
            if(index >= reqCount){
                break;
            }
            request = requests[index];
        }
        //if pq is empty, increase computer time to next request time
        if(pq.pqIsEmpty()){
            computerTime = request.getRequestTime();
        }else{
            //if there is a calculated available computer
            //delete next request from tree and process it
            if(availableComputer > -1){
                PQItemType requestToProcess = PQItemType();
                pq.pqDelete(requestToProcess);
                int reqWaitingTime = computerTime - requestToProcess.getRequestTime();
                compReqFinishTime[availableComputer] = computerTime + requestToProcess.getProcessTime();
                if(printResults)
                    printf("Computer %d takes request %d at ms %d (wait: %d ms)\n", availableComputer, requestToProcess.getId(), computerTime, reqWaitingTime);
                totalWaitingTime += reqWaitingTime;
                availableComputer = -1;
            }else{
                calculateNextAvailableComputer(compReqFinishTime, computerCount, availableComputer, computerTime);
            }   
        }
    }

    free(compReqFinishTime);
    compReqFinishTime = NULL;
    return totalWaitingTime / reqCount;
}

void handleRequests(PQItemType *requests, const int reqCount, const double maxAvWaitTime){
    float avWaitTime;
    int computerCount = 0;

    //create priority queueu with request count
    PriorityQueue pq = PriorityQueue(reqCount);

    //calculate average waiting time with given amount of computers
    //increase computer count if av waiting time larger than its max
    do{
        computerCount++;
        avWaitTime = calculateAverageWaitingTime(pq, requests, reqCount, computerCount, false);
    }while(avWaitTime > maxAvWaitTime);

    //print results with minimum amount of computers needed
    printf("\nMinimum number of computers required: %d\n", computerCount);
    printf("\nSimulation with %d computers:\n\n", computerCount);
    calculateAverageWaitingTime(pq, requests, reqCount, computerCount, true);
    printf("\nAverage waiting time: %f ms\n\n", avWaitTime);
}

int main(int argc, char** argv){
    if(argc < 3){
        cout << "You should define file name and requested average waiting time!";
        return 1;
    }

    //open file
    FILE* file = fopen(argv[1], "r");
    if(file == NULL){
        cout << "Given file cannot be open!";
        return 1;
    }

    //get max average waiting time
    double maxAvWaitTime = stod(argv[2]);

    //get request count
    int reqCount;
    fscanf(file, "%d", &reqCount);
    if(reqCount <= 0){
        cout << "Request count should be valid!";
        return 1; 
    }

    //get requests
    PQItemType *requests = new PQItemType[reqCount];
    for(int i = 0; i < reqCount; i++){
        int id, priority, requestTime, processTime;
        fscanf(file, "%d %d %d %d ", &id, &priority, &requestTime, &processTime);
        requests[i] = PQItemType(id, priority, requestTime, processTime);
    }

    //calculate min amount of computers needed 
    handleRequests(requests, reqCount, maxAvWaitTime);

    //close file, free request array
    fclose(file);
    file = NULL;
    free(requests);
    requests = NULL;
    return 0;
}