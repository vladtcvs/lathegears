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

void make_step(void)
{
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
    encoder_multiplicator_init(&spindel_multiplied_encoder, &spindel_encoder, 256);

    thread_init(&thread, 2, true, &main_screw, &spindel_multiplied_encoder);
    thread_start(&thread);

    int i;
    for (i = 0; i < 100; i++)
    {
        spindel_encoder.callback(&spindel_encoder, true, spindel_encoder.arg);
    }

    return 0;
}
