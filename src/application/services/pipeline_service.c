#include <stdlib.h>
#include <stdio.h>
#include "application/services/pipeline_service.h"
#include "application/repositories/buffer_api.h"
#include "application/services/phase_1_service.h"
#include "application/services/phase_2_service.h"
#include "application/services/phase_3_service.h"

static void fail(pipeline_t *p) {
    pipeline_stop(p);
    pipeline_destroy(p);
}

pipeline_t *pipeline_start(const pipeline_config_t *cfg){
    pipeline_t *p = calloc(1, sizeof *p);

    if (p == NULL) {
        perror("Failed to allocate pipeline");
        return NULL;
    }

    p->buf1 = buffer_init(cfg->buffer1_size);
    if (p->buf1 == NULL) {
        fail(p);
        return NULL;
    }

    p->buf2 = buffer_init(cfg->buffer2_size);
    if (p->buf2 == NULL) {
        fail(p);
        return NULL;
    }

    if(start_phase1(p, cfg->threads_phase1) != 0
        || start_phase2(p, cfg->threads_phase2) != 0
        || start_phase3(p, cfg->threads_phase3) != 0) {
        fail(p);
        return NULL;
    }

    return p;
}

void pipeline_stop(pipeline_t *p) {
    if (p == NULL) return;

    for (int i = 0; i < p->n_p1; i++)
        thread_stop(p->threads_p1[i]);
    for (int i = 0; i < p->n_p2; i++)
        thread_stop(p->threads_p2[i]);
    for (int i = 0; i < p->n_p3; i++)
        thread_stop(p->threads_p3[i]);
}


void pipeline_destroy(pipeline_t *p) {
    if (p == NULL) return;

    for (int i = 0; i < p->n_p1; i++)
        thread_destroy(p->threads_p1[i]);
    free(p->threads_p1);

    for (int i = 0; i < p->n_p2; i++)
        thread_destroy(p->threads_p2[i]);
    free(p->threads_p2);

    for (int i = 0; i < p->n_p3; i++)
        thread_destroy(p->threads_p3[i]);
    free(p->threads_p3);

    if (p->buf1 != NULL) buffer_destroy(p->buf1);
    if (p->buf2 != NULL) buffer_destroy(p->buf2);
    free(p);
}
