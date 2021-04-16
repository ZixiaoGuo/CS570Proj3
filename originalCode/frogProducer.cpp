#include "main.h"

void * frogProducer(void * ptr) {
    BELT_STATUS *belt = (BELT_STATUS *) ptr;

    
    while (true)
    {
        if (sem_trywait(belt->candyLeftToProduce) == -1) {
            pthread_exit(nullptr);
        }
        sem_wait(belt->limitCandyOnBelt); //no more than 10 candies on belt
        sem_wait(belt->mutex);

        //add the candies to the belt
        belt->itemsOnBeltQueue->push("CFB");
        cout << "added candy" << belt->itemsOnBeltQueue->front() << endl;
        //TODO: call io_add_type

        sem_post(belt->mutex);
        

        //usleep(1000 * (*belt->frogWaitTime)); //sleep for time specified in args

        //if total candies = 100 break
    }
    


}

void * escargotProducer(void * ptr) {
    BELT_STATUS *belt = (BELT_STATUS *) ptr;

    
    while (true)
    {
        if (sem_trywait(belt->candyLeftToProduce) == -1) {
            pthread_exit(nullptr);
        }
        sem_wait(belt->limitCandyOnBelt); //no more than 10 candies on belt
        sem_wait(belt->mutex);

        //add the candies to the belt
        belt->itemsOnBeltQueue->push("EES");
        cout << "added candy" << belt->itemsOnBeltQueue->front() << " size of belt is " << belt->itemsOnBeltQueue->size() << endl;
        //TODO: call io_add_type

        sem_post(belt->mutex);
        sem_post(belt->candyLeftToProduce);
        usleep(1000 * (belt->escargotWaitTime)); //sleep for time specified in args

        //if total candies = 100 break
    }
    


}