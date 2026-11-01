#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "buffer_api.h"

buffer_t *buffer_init(int capacity) {
    if (capacity <= 0) {
        fprintf(stderr, "Invalid buffer capacity: %d (must be greater than 0)\n", capacity);
        return NULL;
    }

    buffer_t *b = malloc(sizeof(buffer_t));
    if (b == NULL) {
        perror("Failed to allocate buffer");
        return NULL;
    }

    b->data = malloc((size_t)capacity * sizeof(item_t));
    if (b->data == NULL) {
        perror("Failed to allocate buffer data");
        free(b);
        return NULL;
    }

    b->capacity = capacity;
    b->head = 0;
    b->tail = 0;
    b->count = 0;

    int rc;

    if ((rc = pthread_mutex_init(&b->mutex, NULL)) != 0) {
        fprintf(stderr, "Failed to initialize buffer mutex: %s\n", strerror(rc));
        free(b->data);
        free(b);
        return NULL;
    }
    if ((rc = pthread_cond_init(&b->not_full, NULL)) != 0) {
        fprintf(stderr, "Failed to initialize buffer condition variable (not_full): %s\n", strerror(rc));
        pthread_mutex_destroy(&b->mutex);
        free(b->data);
        free(b);
        return NULL;
    }
    if ((rc = pthread_cond_init(&b->not_empty, NULL)) != 0) {
        fprintf(stderr, "Failed to initialize buffer condition variable (not_empty): %s\n", strerror(rc));
        pthread_cond_destroy(&b->not_full);
        pthread_mutex_destroy(&b->mutex);
        free(b->data);
        free(b);
        return NULL;
    }

    return b;
}

void buffer_destroy(buffer_t *b) {
    if (b == NULL) {
        fprintf(stderr, "Cannot destroy a NULL buffer\n");
        return;
    }

    pthread_cond_destroy(&b->not_empty);
    pthread_cond_destroy(&b->not_full);
    pthread_mutex_destroy(&b->mutex);
    free(b->data);
    free(b);
}

void buffer_put(buffer_t *b, item_t i) {
    if (b == NULL) {
        fprintf(stderr, "Cannot put an item into a NULL buffer\n");
        return;
    }

    pthread_mutex_lock(&b->mutex);

    while (b->count == b->capacity) {
        pthread_cond_wait(&b->not_full, &b->mutex);
    }

    b->data[b->tail] = i;
    b->tail = (b->tail + 1) % b->capacity;
    b->count++;

    pthread_cond_signal(&b->not_empty);
    pthread_mutex_unlock(&b->mutex);
}

void buffer_get(buffer_t *b, item_t *out) {
    if (b == NULL) {
        fprintf(stderr, "Cannot get an item from a NULL buffer\n");
        return;
    }
    if (out == NULL) {
        fprintf(stderr, "Cannot get an item into a NULL output pointer\n");
        return;
    }

    pthread_mutex_lock(&b->mutex);

    while (b->count == 0) {
        pthread_cond_wait(&b->not_empty, &b->mutex);
    }

    *out = b->data[b->head];
    b->head = (b->head + 1) % b->capacity;
    b->count--;

    pthread_cond_signal(&b->not_full);
    pthread_mutex_unlock(&b->mutex);
}