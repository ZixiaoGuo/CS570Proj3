#include "main.h"

void *consumer(void *ptr) {

    ConsumerType consumer;
    ProductType itemBeingConsumed;

    BELT_STATUS * belt = (BELT_STATUS*) ptr;

    sem_wait(belt->consumerTypeGuard);
    if (belt->isLucyStarted == false)
    {
        consumer = Lucy;
        belt->isLucyStarted = true;
        //cout << "setted consumer Lucy" << endl;
    }
    
    else {
        consumer = Ethel;
        //cout << "setted consumer Ethel" << endl;
    }
    sem_post(belt->consumerTypeGuard);
    
    
    while (true) {
        //exit thread if 100th candy already producing
        if (sem_trywait(belt->candyLeftToConsume) == -1) {
            //cout << "exited thread" << endl;
            pthread_exit(nullptr);
        }


        //need to wait until there is candy on belt 
        sem_wait(belt->isBeltEmpty);
        sem_wait(belt->mutex);

        //remove item from belt
        int candyConsumed;


        if (belt->itemsOnBeltQueue->front() == FROG_BITE) {
            sem_post(belt->limitFrogBiteOnBelt);
            itemBeingConsumed = FrogBite;
            belt->candiesOnBelt[itemBeingConsumed]--;
            belt->candiesConsumed[itemBeingConsumed]++;
        }
        else {
            itemBeingConsumed = Escargot;  //consumed EES
            belt->candiesOnBelt[itemBeingConsumed]--;
            belt->candiesConsumed[itemBeingConsumed]++;
        }

        belt->itemsOnBeltQueue->pop();

        //TODO: call io_remove in io class
        io_remove_type(consumer, itemBeingConsumed, belt->candiesOnBelt, belt->candiesConsumed);

        sem_post(belt->mutex);
        sem_post(belt->limitCandyOnBelt);  // add space on the belt since consumed one

        // TODO: wait depends on lucy or ethel
        if (consumer == Lucy) {
            usleep(1000 * (belt->lucyWaitTime)); //sleep for time specified in args
        }

        else {
            usleep(1000 * (belt->ethelWaitTime)); //sleep for time specified in args
        }
        
        //if(belt->totalCandies == 100) {
        //    break;
        //}

    }



}
