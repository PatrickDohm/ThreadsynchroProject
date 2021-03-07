#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "buffer.h"

using namespace std;

void *producer(void *param);
void *consumer(void *param);

/*Parameters are 
1. how long to sleep before terminating
2. the number of producers threads
3. the number of consumer threads
*/
int main(int argc, char *argv[])
{
    if (argc < 4)
    { //expect 4 arguments, the program name, how long to sleep, number of producer threads, number of consumer threads
        printf("You need 4 arguments: 1)program name \n2) how long the main thread sleeps\n3) how many producer threads\n4) how many consumer threads");
        exit(-1);
    }
    
    //1) Get commandline arguments argv[1], argv[2], argv[3]
    int sleepTimer = atoi(argv[1]);
    int numProducers = atoi(argv[2]);
    int numConsumers = atoi(argv[3]);
    //2) initialize buffer
    init_buffer();
   
    //thread init
    pthread_t tid_producer[numProducers]; //the thread identifier
    pthread_t tid_consumer[numConsumers];
    pthread_attr_t attr; //set of thread attributes
    pthread_attr_init(&attr);

    //3) Create producer thread(s)
    for (int i = 0; i < numProducers; i++)
    {
       
        pthread_create(&tid_producer[i], &attr, producer,(void *) &i);
    }

    //4) create consumer thread(s)
    for (int j = 0; j < numConsumers; j++)
    {
        pthread_create(&tid_consumer[j], &attr, consumer,(void *) &j);
    }

    //5) Sleep
    sleep(sleepTimer); //need to convert argv[1] to an int first
    printf("<MAIN THREAD> GOOD BYE \n");
    //6) exit
    return 0;
}

void *producer(void *param)
{
    int producerNumber=*((int *) param);
    buffer_item item;
    srand(time(NULL));
    while (true)
    {
        /* sleep for a random period of time*/
        sleep(rand() % 5);
        //generate a random number
        item = rand()+1;
        if (insert_items(item))
        {
            printf("producer <%d> made an error inserting an item", producerNumber);
        }
        else
        {
            printf("producer <%d> produced %d\n", producerNumber,item);
        }
    }
}

void *consumer(void *param)
{
    buffer_item item = 0; 
    int consumerNumber=*((int *) param);

    while (true)
    {
        //sleep for a random period of time. *note i limit it to 5 seconds for testing purposes
        sleep(rand() % 5);

        if (remove_items(&item))
        {
            printf("consumer <%d> failed to remove the item", consumerNumber);
        }
        else
        {
            printf("consumer <%d> consumed %d\n", consumerNumber,item);
        }
    }
}