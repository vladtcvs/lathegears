#pragma once

#include <stdint.h>
#include <stdbool.h>

struct encoder_s;

typedef void (*encoder_cb_f)(struct encoder_s* encoder, bool dir, void *arg);

struct encoder_s
{
    uint32_t steps;
    encoder_cb_f callback;
    void *arg;
};

void encoder_init(struct encoder_s *encoder, uint32_t steps);
void encoder_register_callback(struct encoder_s *encoder, encoder_cb_f cb, void *arg);
void encoder_pulse(struct encoder_s *encoder, bool dir);
