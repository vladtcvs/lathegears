#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "screw.h"
#include "encoder.h"
#include "common.h"

struct thread_bresenham_s
{
    uint32_t x;
    uint32_t x_max;

    uint32_t y;
    uint32_t y_max;

    uint32_t error;
};

struct thread_desc_s
{
    bool dir;
    uint32_t encoder_steps;
    uint32_t thread_steps;
    bool valid;

    struct screw_desc_s *screw;

    struct  thread_bresenham_s bresenham;
};

void thread_init(struct thread_desc_s *thread, real pitch, bool right, struct screw_desc_s *screw, struct encoder_s *encoder);
void thread_start(struct thread_desc_s *thread);
void thread_on_encoder_cb(struct encoder_s *encoder, bool dir, void *arg);
