#ifndef PIPELINE_SERVICE_H
#define PIPELINE_SERVICE_H

#include "structs/pipeline.h"

pipeline_t *pipeline_start(const pipeline_config_t *cfg);
void pipeline_stop(pipeline_t *p);
void pipeline_destroy(pipeline_t *p);

#endif