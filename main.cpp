#include "main.h"
using namespace std;


int main(int argc, char ** argv) {

    int option;
    bool bigEFlag = false; // milliseconds N that the Ethel consumer requires to put a candy in the box
    bool lFlag = false;     // milliseconds N that the Lucy consumer requires to put a candy in the box
    bool fFlag = false;     // milliseconds requiredto produce each crunchy frog bite
    bool smallEFlag = false; // milliseconds required to produceeach everlasting escargot sucker.

    // initialize variables to pass to struct
    int timeEthel, timeLucy, timeFrog, time_escargot = 0;
    sem_t globalLimitFrogBiteOnBelt;  // no more than 3 CFB on belt
    queue<int> globalBeltContent;
    sem_t globalMutex;
    sem_t globalCandyLeftToProduce;   // stop if 100 ccandies is produced
    sem_t globalLimitCandyOnBelt;     // no more than 10 candies on belt
    sem_t globalIsBeltEmpty;        // let consumer wait if there is no candy on belt

    while ( (option = getopt(argc, argv, "E:L:f:e:")) != -1)
    {
        switch (option)
        {
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

    //pass parameters to update the parameters struct
    status->frogWaitTime = 100;
    status->escargotWaitTime = 100;
    status->lucyWaitTime = 100;
    status->ethelWaitTime = 100;
    status->itemsOnBeltQueue = &globalBeltContent;
    status->totalCandies = 0;
    status->candies_belt = 0;
    status->totalFrogs, status->frogsOnBelt, status->ethelFrogsConsumed, status->lucyFrogConsumed = 0;
    status->mutex = &globalMutex;
    status->candyLeftToProduce = &globalCandyLeftToProduce;
    status->limitCandyOnBelt = &globalLimitCandyOnBelt;
    status->isBeltEmpty = &globalIsBeltEmpty;

    //initialize 4 thread for two producers and consumers
    pthread_t escargotThread;
    pthread_t lucyThread;
    pthread_create(&escargotThread, NULL, escargotProducer, status);
    pthread_create(&lucyThread, NULL, consumer, status);
    pthread_join(escargotThread,nullptr);
    pthread_join(lucyThread,nullptr);

    


    
    //initialize 4 pthreads




    return 0;
}