#include "encoder_multiplicator.h"
#include "common.h"

struct multiplicator_s
{
    int ratio;
    struct encoder_s *mult;
};

#define MAX_MULTIPLICATORS 2

static struct multiplicator_s multiplicators[MAX_MULTIPLICATORS];
static int num = 0;

void encoder_multiplicator_cb(struct encoder_s* source, bool dir, void *arg)
{
    struct multiplicator_s *m = arg;
    struct encoder_s *mult = m->mult;

    int ratio = m->ratio;
    int i;
    for (i = 0; i < ratio; i++)
    {
        encoder_pulse(mult, dir);
    }
}

void encoder_multiplicator_init(struct encoder_s *mult, struct encoder_s *source, int ratio)
{
    if (num >= MAX_MULTIPLICATORS)
    {
        message("Can not create multiplicator");
        return;
    }

    struct multiplicator_s *m = &multiplicators[num++];
    m->mult = mult;
    m->ratio = ratio;

    encoder_init(mult, source->steps * ratio);
    encoder_register_callback(source, encoder_multiplicator_cb, m);
}
