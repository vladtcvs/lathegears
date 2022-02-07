#include "encoder_multiplicator.h"

void encoder_multiplicator_cb(struct encoder_s* source, bool dir, void *arg)
{
    struct encoder_s *mult = arg;

    int ratio = mult->steps / source->steps;
    int i;
    for (i = 0; i < ratio; i++)
    {
        encoder_pulse(mult, dir);
    }
}

void encoder_multiplicator_init(struct encoder_s *mult, struct encoder_s *source, int ratio)
{
    encoder_init(mult, source->steps * ratio);
    encoder_register_callback(source, encoder_multiplicator_cb, mult);
}
