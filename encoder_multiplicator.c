#include "encoder_multiplicator.h"
#include "common.h"

struct multiplicator_s
{
    int ratio;
    struct encoder_s *mult;
    uint32_t queued;
};

#define MAX_MULTIPLICATORS 2

static struct multiplicator_s multiplicators[MAX_MULTIPLICATORS];
static int num = 0;

void encoder_multiplicator_cb(struct encoder_s* source, bool dir, void *arg)
{
    struct multiplicator_s *m = arg;
    struct encoder_s *mult = m->mult;

    int ratio = m->ratio;
    m->queued += ratio;

    int i;
    uint32_t n = m->queued;
    for (i = 0; i < n; i++)
    {
        encoder_pulse(mult, dir);
        m->queued--;
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
    m->queued = 0;

    encoder_init(mult, source->steps * ratio);
    encoder_register_callback(source, encoder_multiplicator_cb, m);
}
