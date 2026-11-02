#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "application/services/phase_2_service.h"
#include "application/repositories/buffer_api.h"

static void *phase2_run(void *arg) {
    phase2_thread *self = (phase2_thread *)arg;

    printf("[phase2 #%d] running\n", self->id);

    return NULL;
}

static int phase2_init(thread_node_i *iface, thread_fn fn) {
    phase2_thread *self = (phase2_thread *)iface;

    if (self->started)
        return EALREADY;

    thread_fn routine = fn ? fn : iface->run;

    atomic_store(&self->stop_requested, 0);
    int rc = pthread_create(&self->tid, NULL, routine, self);
    if (rc == 0)
        self->started = 1;

    return rc;
}

static void phase2_stop(thread_node_i *iface) {
    phase2_thread *self = (phase2_thread *)iface;

    if (!self->started || self->joined)
        return;

    atomic_store(&self->stop_requested, 1);

    pthread_join(self->tid, NULL);
    self->joined = 1;
}

static void phase2_destroy(thread_node_i *iface) {
    phase2_thread *self = (phase2_thread *)iface;

    if (self == NULL)
        return;

    iface->stop(iface);
    free(self);
}

thread_node_i *phase2_create(int id, buffer_t *in, buffer_t *out) {
    phase2_thread *t = calloc(1, sizeof *t);
    if (t == NULL) {
        perror("Failed to allocate phase1 thread");
        return NULL;
    }

    t->base.init = phase2_init;
    t->base.stop = phase2_stop;
    t->base.destroy = phase2_destroy;
    t->base.run = phase2_run;
    t->id = id;
    t->in = in;
    t->out = out;
    atomic_init(&t->stop_requested, 0);

    return &t->base;
}

int start_phase2(pipeline_t *p, int n) {
    p->threads_p2 = malloc(n * sizeof(*p->threads_p1));

    if (p->threads_p2 == NULL) {
        perror("Failed to allocate phase1 threads.");
        return -1;
    }

    p->n_p2=0;

    for (int i = 0; i < n; i++) {
        thread_node_i *t = phase2_create(i, p->buf1, p->buf2);

        if (t == NULL)
            return -1;

        p->threads_p2[i] = t;
        p->n_p2++;

        if (thread_init(t, NULL) != 0){
            fprintf(stderr, "Failed to start phase1 thread %d\n", i);
            return -1;
        }
    }

    return 0;
}
