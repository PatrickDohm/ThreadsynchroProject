// buffer.h
typedef int buffer_item;
#define BUFFER_SIZE 5

//function prototypes
int insert_items(buffer_item item);
int remove_items(buffer_item *item);