#include "encoder.h"

void encoder_register_callback(struct encoder_s *encoder, encoder_cb_f cb, void *arg)
{
    encoder->callback = cb;
    encoder->arg = arg;
}

void encoder_init(struct encoder_s *encoder, uint32_t steps)
{
    encoder->steps = steps;
}

void encoder_pulse(struct encoder_s *encoder, bool dir)
{
    if (encoder->callback)
        encoder->callback(encoder, dir, encoder->arg);
}
