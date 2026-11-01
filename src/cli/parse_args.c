#include "cli/parse_args.h"
#include <stdio.h>
#include <stdlib.h>

arg_t * parse_arguments(int argc, char ** argv){
    if (argc != 6){
        const char *program = (argc > 0 && argv[0] != NULL) ? argv[0] : "pipelined-producer-consumer";
        fprintf(stderr, "Usage: %s <threads phase 1> <threads phase 2> <threads phase 3> <buffer size 1> <buffer size 2>\n", program);
        return NULL;
    }

    arg_t * args = malloc(sizeof(arg_t));

    if (args == NULL) {
        perror("Failed to allocate arguments");
        return NULL;
    }

    args->NUM_THREADS_P1 = atoi(argv[1]);
    args->NUM_THREADS_P2 = atoi(argv[2]);
    args->NUM_THREADS_P3 = atoi(argv[3]);
    args->BUF_1_SIZE = atoi(argv[4]);
    args->BUF_2_SIZE = atoi(argv[5]);

    return args;
}