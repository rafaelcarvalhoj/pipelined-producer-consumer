#ifndef PROGRAM_ARGS_H
#define PROGRAM_ARGS_H

typedef struct {
    int NUM_THREADS_P1, 
        NUM_THREADS_P2,
        NUM_THREADS_P3;

    int BUF_1_SIZE, 
        BUF_2_SIZE;
} arg_t;

#endif