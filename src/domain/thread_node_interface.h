#ifndef THREAD_NODE_INTERFACE_H
#define THREAD_NODE_INTERFACE_H

typedef void *(*thread_fn)(void *args);

typedef struct thread_node_i thread_node_i;

struct thread_node_i {
    int (*init)(thread_node_i *self, thread_fn fn);
    void (*stop)(thread_node_i *self);
    void (*destroy)(thread_node_i *self);
    void *(*run)(void *self);
};

static inline int thread_init(thread_node_i *t, thread_fn fn) {
    return t->init(t, fn);
}

static inline void thread_stop(thread_node_i *t) {
    t->stop(t);
}

static inline void thread_destroy(thread_node_i *t) {
    t->destroy(t);
}

#endif