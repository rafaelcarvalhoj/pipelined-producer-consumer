#ifndef PIPELINE_H
#define PIPELINE_H

#include "structs/buffer.h"
#include "domain/thread_node_interface.h"

typedef struct {
    int threads_phase1;
    int threads_phase2;
    int threads_phase3;
    int buffer1_size;
    int buffer2_size;
} pipeline_config_t;

typedef struct {
    buffer_t *buf1;
    buffer_t *buf2;

    thread_node_i **threads_p1;
    thread_node_i **threads_p2;
    thread_node_i **threads_p3;

    int n_p1, n_p2, n_p3;
} pipeline_t;

#endif