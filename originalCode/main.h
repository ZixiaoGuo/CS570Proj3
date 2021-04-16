#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <pthread.h>
#include <sched.h>	/* Only necessary for sched_yield */
#include <semaphore.h>
#include <vector>
#include <string>
#include <time.h>   //for nanosleep
#include <unistd.h>
#include <queue>       
#include <iostream>   
#include <stdlib.h>  
#include <getopt.h>  
using namespace std;

//int totalCandyProduced = 0;





typedef struct {
    // waiting times
    int frogWaitTime;
    int escargotWaitTime;
    int lucyWaitTime;
    int ethelWaitTime;

    //pass pointer of belt
    queue<string> *itemsOnBeltQueue;

    int totalCandies, candies_belt;   
    
    int totalFrogs; // total CFB candies produced
    int frogsOnBelt; //number of frogs on belt
    int ethelFrogsConsumed, lucyFrogConsumed; //total frog consumed by two consumers

    // similiar variables for Escargot
    int totalEscargot, escargotsOnBelt, ethelEscargotConsumed,lucyEscargotConsumed;

    sem_t *mutex;
    sem_t *candyLeftToProduce;   // stop if 100 ccandies is produced
    sem_t *limitCandyOnBelt;     // no more than 10 candies on belt

} BELT_STATUS;



void *consumer(void *ptr);
void *escargotProducer(void *ptr);
void *frogProducer(void *ptr);

#endif