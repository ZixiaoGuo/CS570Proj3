#include "main.h"

void * frogProducer(void * ptr) {
    BELT_STATUS *belt = (BELT_STATUS *) ptr;
    ProductType producer = FrogBite;
    
    while (true)
    {
        if (sem_trywait(belt->candyLeftToProduce) == -1) {
            //cout << "exited frog thread" << endl;
            pthread_exit(nullptr);
        }
        //cout << "global Frog wait time: ++++++++++++++ " << globalFrogWaitTime << endl;

        sem_wait(belt->limitCandyOnBelt); //no more than 10 candies on belt
        sem_wait(belt->limitFrogBiteOnBelt);

        //cout << "frog waiting mutex" << endl;
        sem_wait(belt->mutex);

        //add the candies to the belt
        belt->itemsOnBeltQueue->push(FROG_BITE); //push frog bite(0) to the queue
        belt->totalCandies++;
        //TODO: call io_add_type

        //cout << endl;
        //cout << "producedFrogBite" << endl;
        //cout << endl;
        
        belt->candiesOnBelt[FrogBite]++;
        belt->candiesProduced[FrogBite]++;
        io_add_type(producer, belt->candiesOnBelt, belt->candiesProduced);

        sem_post(belt->mutex);
        sem_post(belt->isBeltEmpty);
        usleep(1000 * belt->frogWaitTime); //sleep for time specified in args

        //if total candies = 100 break
    }
    


}

void * escargotProducer(void * ptr) {
    BELT_STATUS *belt = (BELT_STATUS *) ptr;
    ProductType producer = Escargot;

    
    while (true)
    {
        if (sem_trywait(belt->candyLeftToProduce) == -1) {
            //cout << "exited escargot thread" << endl;

            pthread_exit(nullptr);
        }
        sem_wait(belt->limitCandyOnBelt); //no more than 10 candies on belt
        sem_wait(belt->mutex);

        //add the candies to the belt
        belt->itemsOnBeltQueue->push(ESCARGOT);
        belt->totalCandies++;
        //TODO: call io_add_type
        belt->candiesOnBelt[Escargot]++;
        belt->candiesProduced[Escargot]++;
        io_add_type(producer, belt->candiesOnBelt, belt->candiesProduced);

        sem_post(belt->mutex);
        sem_post(belt->isBeltEmpty);
        usleep(1000 * belt->escargotWaitTime); //sleep for time specified in args

        //if total candies = 100 break
    }
    


}