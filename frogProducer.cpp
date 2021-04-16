#include "main.h"

void * frogProducer(void * ptr) {
    BELT_STATUS *belt = (BELT_STATUS *) ptr;

    
    while (true)
    {
        if (sem_trywait(belt->candyLeftToProduce) == -1) {
            cout << "exited thread" << endl;
            pthread_exit(nullptr);
        }
        sem_wait(belt->limitCandyOnBelt); //no more than 10 candies on belt
        sem_wait(belt->limitFrogBiteOnBelt);
        sem_wait(belt->mutex);

        //add the candies to the belt
        belt->itemsOnBeltQueue->push(FROG_BITE); //push frog bite(1) to the queue
        cout << "added candy " << belt->itemsOnBeltQueue->front() << " size of belt is " << belt->itemsOnBeltQueue->size() << endl;
        belt->totalCandies++;
        cout << "total candies produced is " << belt->totalCandies << endl;
        cout << endl;
        //TODO: call io_add_type

        sem_post(belt->mutex);
        //sem_post(belt->candyLeftToProduce);
        sem_post(belt->isBeltEmpty);
        usleep(1000 * (belt->frogWaitTime)); //sleep for time specified in args

        //if total candies = 100 break
    }
    


}

void * escargotProducer(void * ptr) {
    BELT_STATUS *belt = (BELT_STATUS *) ptr;

    
    while (true)
    {
        if (sem_trywait(belt->candyLeftToProduce) == -1) {
            cout << "exited thread" << endl;

            pthread_exit(nullptr);
        }
        sem_wait(belt->limitCandyOnBelt); //no more than 10 candies on belt
        sem_wait(belt->mutex);

        //add the candies to the belt
        belt->itemsOnBeltQueue->push(ESCARGOT);
        cout << endl;
        cout << "added candy " << belt->itemsOnBeltQueue->front() << ", size of belt is " << belt->itemsOnBeltQueue->size() << endl;
        belt->totalCandies++;
        cout << "total candies produced is " << belt->totalCandies << endl;
        cout << endl;
        //TODO: call io_add_type

        sem_post(belt->mutex);
        sem_post(belt->isBeltEmpty);
        usleep(1000 * (belt->escargotWaitTime)); //sleep for time specified in args

        //if total candies = 100 break
    }
    


}