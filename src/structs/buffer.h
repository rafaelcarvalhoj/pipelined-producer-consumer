#ifndef BUFFER_TYPE_H
#define BUFFER_TYPE_H

#include <pthread.h>


typedef struct {
    int data;
} item_t;

typedef struct {
    item_t * data;
    int capacity, count;
    int head, tail;
    pthread_mutex_t mutex;
    pthread_cond_t not_full, not_empty;
} buffer_t;

#endif