#include <stdio.h>

#include "encoder.h"
#include "screw.h"
#include "threads.h"

#include "encoder_multiplicator.h"


struct encoder_s spindel_encoder;
struct encoder_s spindel_multiplied_encoder;

struct screw_desc_s main_screw;

struct thread_desc_s thread;

static bool sdir;
void set_dir(bool dir)
{
    sdir = dir;
}

int tsteps = 0;

void make_step(void)
{
    tsteps++;
    return;
    if (sdir)
        printf("+\n");
    else
        printf("-\n");
}

void message(const char *msg)
{
    puts(msg);
}

int main(void)
{
    int steps = 200;
    int microsteps = 2;
    int ratio = 3;

    main_screw.dir = false;
    main_screw.pitch = 2.0;
    main_screw.steps = steps * microsteps * ratio;
    main_screw.set_dir = set_dir;
    main_screw.make_step = make_step;

    encoder_init(&spindel_encoder, 100);
    encoder_multiplicator_init(&spindel_multiplied_encoder, &spindel_encoder, 128);

    thread_init(&thread, 2, true, &main_screw, &spindel_multiplied_encoder);
    thread_start(&thread);

    int i, j;
    for (i = 0; i < 100; i++)
    {
        encoder_pulse(&spindel_encoder, true);
        for (j = 0; j < 1000; j++)
            encoder_multiplicator_timer_tick();
    }

    for (j = 0; j < 400000; j++)
            encoder_multiplicator_timer_tick();

    printf("%i\n", tsteps);

    return 0;
}
