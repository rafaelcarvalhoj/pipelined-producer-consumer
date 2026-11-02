#ifndef MAIN_PROG
#define MAIN_PROG

#include <stdio.h>
#include "cli/parse_args.h"
#include "structs/pipeline.h"
#include "application/services/pipeline_service.h"

void print_startup(){
    puts("CIC0202 - Programação Concorrente | 2026.2");
    puts("Professor: Eduardo Alchieri");
    puts("---------------------------------------------");
    puts("Aluno: Rafael Carvalho Junior Araújo");
    puts("Matrícula: 222021817");
    puts("---------------------------------------------");
    puts("Produtor-Consumidor: Pipeline três estágios com dois buffers + interrupção externa.");
}

void print_arguments(const arg_t *args){
    printf("Threads nó 1: %d\n", args->NUM_THREADS_P1);
    printf("Threads nó 2: %d\n", args->NUM_THREADS_P2);
    printf("Threads nó 3: %d\n", args->NUM_THREADS_P3);
    printf("Buffer entre nós 1 e nós 2: %d\n", args->BUF_1_SIZE);
    printf("Buffer entre nós 2 e nós 3: %d\n", args->BUF_2_SIZE);
}

int main(int argc, char* argv[]){
    print_startup();
    
    arg_t * args = parse_arguments(argc, argv);
    if (args == NULL) {
        return -1;
    }

    print_arguments(args);

    pipeline_config_t cfg = {
        .threads_phase1 = args->NUM_THREADS_P1,
        .threads_phase2 = args->NUM_THREADS_P2,
        .threads_phase3 = args->NUM_THREADS_P3,
        .buffer1_size   = args->BUF_1_SIZE,
        .buffer2_size   = args->BUF_2_SIZE,
    };
    
    pipeline_t *p = pipeline_start(&cfg);

    pipeline_stop(p);

    pipeline_destroy(p);
    return 0;
}


#endif
