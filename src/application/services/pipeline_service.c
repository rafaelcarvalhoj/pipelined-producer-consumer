#include <stdlib.h>
#include <stdio.h>
#include "application/services/pipeline_service.h"
#include "application/repositories/buffer_api.h"

pipeline_t *pipeline_start(const pipeline_config_t *cfg){
    pipeline_t *p = malloc(sizeof(pipeline_t));

    if (p == NULL) {
        perror("Failed to allocate pipeline");
        return NULL;
    }

    // buffers
    p->buf1 = buffer_init(cfg->buffer1_size);
    p->buf2 = buffer_init(cfg->buffer2_size);

    // threads
    puts(">> TODO: PHASE 1 THREADS INIT");
    p->n_p1 = NULL;
    puts(">> TODO: PHASE 2 THREADS INIT");
    p->n_p2 = NULL;
    puts(">> TODO: PHASE 3 THREADS INIT");
    p->n_p3 = NULL;

    return p;
}

void pipeline_stop(pipeline_t *p) {
    puts(">> TODO: PIPELINE STOP");
}


void pipeline_destroy(pipeline_t *p) {
    buffer_destroy(p->buf1);
    buffer_destroy(p->buf2);
    puts(">> TODO: PHASE 1 THREADS DESTROY");
    puts(">> TODO: PHASE 2 THREADS DESTROY");
    puts(">> TODO: PHASE 3 THREADS DESTROY");
}