

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "buffer.h"


using namespace std;

void *producer(void* param);
void *consumer(void* param);

/*Parameters are 
1. how long to sleep before terminating
2. the number of producers threads
3. the number of consumer threads
*/
int main(int argc, char *argv[]){
//1) Get commandline arguments argv[1], argv[2], argv[3]

//2) initialize buffer


//thread init
pthread_t tid_producer; //the thread identifier
pthread_t tid_consumer;
pthread_attr_t attr; //set of thread attributes
pthread_attr_init(&attr);

//3) Create producer thread(s)
pthread_create(&tid_producer,&attr,producer,argv[1]); //will need to change this later to incorporate multiple producers and adjust what gets passed to function
//4) create consumer thread(s)
pthread_create(&tid_consumer,&attr,consumer, argv[1]);
//5) Sleep
sleep(argv[1]);//need to convert argv[1] to an int first
//6) exit
exit(1);

}

void *producer(void* param){
    buffer_item item;
    srand(time(NULL));
    while(true){
        /* sleep for a random period of time*/
        sleep(rand()%5);
        //generate a random number
        item=rand();
        if(insert_items(item)){
            printf("producer made an error inserting an item");
        }else{
            printf("producer produced %d\n", item);
        }

    }
}

void *consumer(void* param){
    buffer_item item;

    while(true){
        //sleep for a random period of time. *note i limit it to 5 seconds for testing purposes
        sleep(rand()%5);

        if(remove_items(&item)){
            printf("consumer failed to remove the item");
        }else{
            printf("consumer consumed %d\n", item);
        }

    }
}