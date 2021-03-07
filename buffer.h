// buffer.h

#ifndef BUFFER_H
#define BUFFER_H
typedef int buffer_item;
#define BUFFER_SIZE 5

//function prototypes
void init_buffer();
int insert_items(buffer_item item);
int remove_items(buffer_item *item);

#endif