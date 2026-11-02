#ifndef PHASE3_SERVICE_H
#define PHASE3_SERVICE_H

#include <pthread.h>
#include <stdatomic.h>

#include "domain/thread_node_interface.h"
#include "structs/buffer.h"
#include "structs/pipeline.h"

typedef struct {
    thread_node_i base;
    pthread_t tid;
    atomic_bool stop_requested;
    int started;
    int joined;
    int id;
    buffer_t *in;
} phase3_thread;

thread_node_i *phase3_create(int id, buffer_t *in);

int start_phase3(pipeline_t *p, int n);

#endif
