#ifndef PHASE2_SERVICE_H
#define PHASE2_SERVICE_H

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
    buffer_t *in, *out;

} phase2_thread;

thread_node_i *phase2_create(int id, buffer_t *in, buffer_t *out);

int start_phase2(pipeline_t *p, int n);

#endif