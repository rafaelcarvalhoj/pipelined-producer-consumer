#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "application/services/phase_1_service.h"
#include "application/repositories/buffer_api.h"

static void *phase1_run(void *arg) {
    phase1_thread *self = (phase1_thread *)arg;

    printf("[phase1 #%d] running\n", self->id);

    return NULL;
}

static int phase1_init(thread_node_i *iface, thread_fn fn) {
    phase1_thread *self = (phase1_thread *)iface;

    if (self->started)
        return EALREADY;

    thread_fn routine = fn ? fn : iface->run;

    atomic_store(&self->stop_requested, 0);
    int rc = pthread_create(&self->tid, NULL, routine, self);
    if (rc == 0)
        self->started = 1;

    return rc;
}

static void phase1_stop(thread_node_i *iface) {
    phase1_thread *self = (phase1_thread *)iface;

    if (!self->started || self->joined)
        return;

    atomic_store(&self->stop_requested, 1);

    pthread_join(self->tid, NULL);
    self->joined = 1;
}

static void phase1_destroy(thread_node_i *iface) {
    phase1_thread *self = (phase1_thread *)iface;

    if (self == NULL)
        return;

    iface->stop(iface);
    free(self);
}

thread_node_i *phase1_create(int id, buffer_t *out) {
    phase1_thread *t = calloc(1, sizeof *t);
    if (t == NULL) {
        perror("Failed to allocate phase1 thread");
        return NULL;
    }

    t->base.init    = phase1_init;
    t->base.stop    = phase1_stop;
    t->base.destroy = phase1_destroy;
    t->base.run     = phase1_run;

    t->id  = id;
    t->out = out;
    atomic_init(&t->stop_requested, 0);

    return &t->base;
}

int start_phase1(pipeline_t *p, int n) {
    p->threads_p1 = malloc(n * sizeof(*p->threads_p1));

    if (p->threads_p1 == NULL) {
        perror("Failed to allocate phase1 threads.");
        return -1;
    }

    p->n_p1=0;

    for (int i = 0; i < n; i++) {
        thread_node_i *t = phase1_create(i, p->buf1);

        if (t == NULL)
            return -1;

        p->threads_p1[i] = t;
        p->n_p1++;

        if (thread_init(t, NULL) != 0){
            fprintf(stderr, "Failed to start phase1 thread %d\n", i);
            return -1;
        }
    }

    return 0;
}
