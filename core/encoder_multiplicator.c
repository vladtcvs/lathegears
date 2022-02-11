#include "encoder_multiplicator.h"
#include "common.h"

void message(const char *msg);

struct multiplicator_s
{
    int ratio;
    struct encoder_s *mult;
    uint32_t queued;
    bool dir;

    uint32_t max_ticks;

    uint32_t ticks;
    uint32_t num_ticks;
    uint32_t step_ticks;
};

static struct multiplicator_s multiplicators[MAX_MULTIPLICATORS];
static int num = 0;

void encoder_multiplicator_cb(struct encoder_s* source, bool dir, void *arg)
{
    struct multiplicator_s *m = arg;

    m->dir = dir;
    m->queued += m->ratio;

    m->num_ticks = m->ticks;
    m->ticks = 0;
}

void encoder_multiplicator_init(struct encoder_s *mult, struct encoder_s *source, int ratio, uint32_t max_ticks)
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
    m->max_ticks = max_ticks;

    encoder_init(mult, source->steps * ratio);
    encoder_register_callback(source, encoder_multiplicator_cb, m);
}

void encoder_multiplicator_timer_tick(void)
{
    int i;
    for (i = 0; i < num; i++)
    {
        struct multiplicator_s *m = &multiplicators[i];

       	if (m->ticks < m->max_ticks)
            m->ticks++;

        if (m->queued > 0)
        {
            m->step_ticks++;

            int ratio = m->ratio;
            if (m->queued > ratio*1.5)
            {
                ratio *= 2;
            }
            else if (m->queued > ratio)
            {
                ratio *= 1.5;
            }

            if (m->step_ticks * ratio > m->num_ticks)
            {
                m->step_ticks = 0;
                encoder_pulse(m->mult, m->dir);
                m->queued--;
            }
        }
    }
}

