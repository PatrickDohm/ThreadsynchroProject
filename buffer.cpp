#include "buffer.h"
#include <pthread.h>
#include <semaphore.h>

//the buffer
buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex; //ME to the in and out counter
sem_t empty;
sem_t full;
int in = 0;
int out = 0;

void init_buffer()
{ //init buffer to 0 and init mutex,full, empty
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        buffer[i] = 0;
    }
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
}
int insert_items(buffer_item item)
{
    //insert item into buffer
    sem_wait(&empty);
     //we need to lock this section
    if (buffer[in] != 0)
    { //0 means empty
       
        return -1;
    }
    buffer[in] = item;
    pthread_mutex_lock(&mutex);
    in = (in + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    return 0; //return 0 if successful
    //return -1 indicating an error condition
}

int remove_items(buffer_item *item)
{
    sem_wait(&full);
    //we need to lock this section
    if (buffer[out] == 0)
    {
      
        return -1;
    }
    *item = buffer[out];
    buffer[out]=0;
    pthread_mutex_lock(&mutex); 
    out = (out + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    return 0; //return 0 if successful
    //return -1 indicating an error condition
}