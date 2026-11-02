#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "application/services/phase_3_service.h"

static void *phase3_run(void *arg) {
    phase3_thread *self = (phase3_thread *)arg;

    printf("[phase3 #%d] running\n", self->id);

    return NULL;
}

static int phase3_init(thread_node_i *iface, thread_fn fn) {
    phase3_thread *self = (phase3_thread *)iface;

    if (self->started)
        return EALREADY;

    thread_fn routine = fn ? fn : iface->run;

    atomic_store(&self->stop_requested, 0);
    int rc = pthread_create(&self->tid, NULL, routine, self);
    if (rc == 0)
        self->started = 1;

    return rc;
}

static void phase3_stop(thread_node_i *iface) {
    phase3_thread *self = (phase3_thread *)iface;

    if (!self->started || self->joined)
        return;

    atomic_store(&self->stop_requested, 1);

    pthread_join(self->tid, NULL);
    self->joined = 1;
}

static void phase3_destroy(thread_node_i *iface) {
    phase3_thread *self = (phase3_thread *)iface;

    if (self == NULL)
        return;

    iface->stop(iface);
    free(self);
}

thread_node_i *phase3_create(int id, buffer_t *in) {
    phase3_thread *t = calloc(1, sizeof *t);
    if (t == NULL) {
        perror("Failed to allocate phase3 thread");
        return NULL;
    }

    t->base.init = phase3_init;
    t->base.stop = phase3_stop;
    t->base.destroy = phase3_destroy;
    t->base.run = phase3_run;
    t->id = id;
    t->in = in;
    atomic_init(&t->stop_requested, 0);

    return &t->base;
}

int start_phase3(pipeline_t *p, int n) {
    p->threads_p3 = malloc((size_t)n * sizeof(*p->threads_p3));
    if (p->threads_p3 == NULL) {
        perror("Failed to allocate phase3 threads");
        return -1;
    }

    p->n_p3 = 0;

    for (int i = 0; i < n; i++) {
        thread_node_i *t = phase3_create(i, p->buf2);
        if (t == NULL)
            return -1;

        p->threads_p3[i] = t;
        p->n_p3++;

        if (thread_init(t, NULL) != 0) {
            fprintf(stderr, "Failed to start phase3 thread %d\n", i);
            return -1;
        }
    }

    return 0;
}
