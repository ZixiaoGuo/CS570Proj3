#include "main.h"
using namespace std;


int main(int argc, char ** argv) {

    int option;
    
    bool fFlag = false;     // milliseconds requiredto produce each crunchy frog bite
    bool smallEFlag = false; // milliseconds required to produceeach everlasting escargot sucker.
    bool bigEFlag = false; // milliseconds N that the Ethel consumer requires to put a candy in the box
    bool lFlag = false;     // milliseconds N that the Lucy consumer requires to put a candy in the box
    // initialize variables to pass to struct
    int timeEthel, timeLucy, timeFrog, time_escargot = 0;
    sem_t globalLimitFrogBiteOnBelt;  // no more than 3 CFB on belt
    queue<int> globalBeltContent;
    sem_t globalMutex;
    sem_t globalCandyLeftToProduce;   // stop if 100 candies is produced
    sem_t globalLimitCandyOnBelt;     // no more than 10 candies on belt
    sem_t globalIsBeltEmpty;        // let consumer wait if there is no candy on belt
    sem_t globalCandyLeftToConsume;   // stop if 100 candies is consumed
    sem_t globalConsumerTypeGuard;  // barrier for setting the type of consumer


    while ( (option = getopt(argc, argv, "f:e:E:L:")) != -1)
    {
        switch (option)
        {
            case 'f': /* frog bite, N = number of miliseconds */
                fFlag = true;
                timeFrog = atoi(optarg);
                //printf("frog bites %d\n", frog_N);
                break;
            
            case 'e': /* escargot, N = number of miliseconds */
                smallEFlag = true;
                time_escargot = atoi(optarg);
                //printf("escargot %d\n", escar_N);
                break;

            case 'E': /* Ethel consumer, N = number of miliseconds */
                bigEFlag = true;
                timeEthel = atoi(optarg);
                //printf("Ethel %d\n", Ethel_N);
                break;

            case 'L': /* Lucy consumer, N = number of miliseconds */
                lFlag = true;
                timeLucy = atoi(optarg);
                //printf("Lucy %d\n", Lucy_N);
                break;


        }
    }

    //these variables only used to set parameters, will not use globally


    //initialize struct
    BELT_STATUS *status = new BELT_STATUS;

    //initialize semaphores
    sem_init(&globalLimitFrogBiteOnBelt, 0, 3);
    sem_init(&globalMutex, 0, 1);
    sem_init(&globalCandyLeftToProduce, 0, 100);
    sem_init(&globalLimitCandyOnBelt, 0, 10);
    sem_init(&globalIsBeltEmpty, 0, 0);
    sem_init(&globalCandyLeftToConsume, 0, 100);
    sem_init(&globalConsumerTypeGuard, 0, 1);

    //pass parameters to update the parameters struct
    status->frogWaitTime = timeFrog;
    status->escargotWaitTime = time_escargot;
    status->ethelWaitTime = timeEthel;
    status->lucyWaitTime = timeLucy;
    status->itemsOnBeltQueue = &globalBeltContent;
    status->totalCandies = 0;
    status->totalFrogs, status->frogsOnBelt, status->ethelFrogsConsumed, status->lucyFrogConsumed = 0;
    status->mutex = &globalMutex;
    status->candyLeftToProduce = &globalCandyLeftToProduce;
    status->limitCandyOnBelt = &globalLimitCandyOnBelt;
    status->limitFrogBiteOnBelt = &globalLimitFrogBiteOnBelt;
    status->isBeltEmpty = &globalIsBeltEmpty;
    status->candyLeftToConsume = &globalCandyLeftToConsume;
    status->consumerTypeGuard = &globalConsumerTypeGuard;

    status->isLucyStarted = false;

    status->candiesOnBelt[0] = 0;
    status->candiesOnBelt[1] = 0;
    status->candiesProduced[0] = 0;
    status->candiesProduced[1] = 0;
    status->candiesConsumed[0] = 0;
    status->candiesConsumed[1] = 0;


    

    //initialize 4 thread for two producers and consumers
    pthread_t escargotThread;
    pthread_t lucyThread;
    pthread_t frogThread;
    pthread_t ethelThread;
    pthread_create(&frogThread, NULL, frogProducer, (void*)status);
    pthread_create(&escargotThread, NULL, escargotProducer, (void *)status);
    pthread_create(&lucyThread, NULL, consumer, (void *)status);
    pthread_create(&ethelThread, NULL, consumer, (void *)status);

    pthread_join(frogThread, nullptr);
    pthread_join(escargotThread,nullptr);
    pthread_join(lucyThread,nullptr);
    pthread_join(ethelThread,nullptr);


    
    sem_destroy(&globalLimitFrogBiteOnBelt);
    sem_destroy(&globalMutex);
    sem_destroy(&globalCandyLeftToProduce);
    sem_destroy(&globalLimitCandyOnBelt);
    sem_destroy(&globalIsBeltEmpty);
    sem_destroy(&globalCandyLeftToConsume);
    sem_destroy(&globalConsumerTypeGuard);



    return 0;
}