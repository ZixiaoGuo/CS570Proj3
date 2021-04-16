#include "main.h"

void *consumer(void *ptr) {

    BELT_STATUS * belt = (BELT_STATUS*) ptr;
    
    while (true) {
        //exit thread if 100th candy already producing
        if (sem_trywait(belt->candyLeftToProduce) == -1) {
            pthread_exit(nullptr);
        }
        sem_wait(belt->mutex);

        //remove item from belt
        
        //call io_remove in io class

        sem_post(belt->mutex);
        sem_post(belt->limitCandyOnBelt);  // add space on the belt since consumed one

        // TODO: wait depends on lucy or ethel
        //usleep(1000 * (*belt->lucyWaitTime)); //sleep for time specified in args
        if(belt->totalCandies == 100) {
            break;
        }

    }



}