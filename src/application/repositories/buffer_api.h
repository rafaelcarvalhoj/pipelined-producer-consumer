#ifndef BUFFER_API_H
#define BUFFER_API_H

#include "structs/buffer.h"

buffer_t *buffer_init(int capacity);

void buffer_destroy(buffer_t *b);

void buffer_put(buffer_t *b, item_t i);

void buffer_get(buffer_t *b, item_t *out);

#endif