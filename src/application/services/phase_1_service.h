#ifndef PHASE1_SERVICE_H
#define PHASE1_SERVICE_H

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
    buffer_t *out;

} phase1_thread;

thread_node_i *phase1_create(int id, buffer_t *out);

int start_phase1(pipeline_t *p, int n);

#endif