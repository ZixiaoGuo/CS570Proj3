#include "main.h"

void *consumer(void *ptr) {

    BELT_STATUS * belt = (BELT_STATUS*) ptr;
    
    while (true) {
        //exit thread if 100th candy already producing
        if (sem_trywait(belt->candyLeftToConsume) == -1) {
            cout << "exited thread" << endl;
            pthread_exit(nullptr);
        }

        sem_wait(belt->isBeltEmpty);
        sem_wait(belt->mutex);
        //TODO: need to wait until there is candy on belt 


        //remove item from belt
        int candyConsumed;
        cout << "item count before consume " << belt->itemsOnBeltQueue->size() << endl;
        cout << "items removed from belt " << belt->itemsOnBeltQueue->front() << endl;
        belt->itemsOnBeltQueue->pop();
        cout << "item count after remove " << belt->itemsOnBeltQueue->size() << endl;
        cout << "next item to be remove from belt " << belt->itemsOnBeltQueue->front();
        cout << endl;

        
        //TODO: call io_remove in io class

        sem_post(belt->mutex);
        sem_post(belt->limitCandyOnBelt);  // add space on the belt since consumed one

        // TODO: wait depends on lucy or ethel
        usleep(1000 * (belt->lucyWaitTime)); //sleep for time specified in args
        //if(belt->totalCandies == 100) {
        //    break;
        //}

    }



}
