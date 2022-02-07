#include "threads.h"

#include <stdbool.h>
#include <stdint.h>

void thread_init(struct thread_desc_s *thread, real pitch, bool right, struct screw_desc_s *screw, struct encoder_s *encoder)
{
    /**
     * Amount of screw steps per spindel rotation:
     *
     * thread_steps = screw_steps * pitch / screw_pitch
     * 
     * Amount of encoder steps per spindel rotation:
     * 
     * encoder_steps
     *
     * We will use 16 * thread_steps and 16 * encoder_steps for bresenham planning
     */

    uint32_t screw_steps = screw->steps;
    real screw_pitch     = screw->pitch;

    real thread_steps = screw_steps * pitch / screw_pitch;

    thread->valid = true;

    thread->screw = screw;

    thread->dir = (right != screw->dir);
    thread->encoder_steps = 16 * encoder->steps;
    thread->thread_steps = (uint32_t)(16 * thread_steps + 0.5);

    if (thread->encoder_steps < thread->thread_steps)
    {
        message("Multiple steps thread!");
        thread->valid = false;
        return;
    }

    encoder_register_callback(encoder, thread_on_encoder_cb, thread);
}

void thread_start(struct thread_desc_s *thread)
{
    thread->bresenham.x = 0;
    thread->bresenham.x_max = thread->encoder_steps;

    thread->bresenham.y = 0;
    thread->bresenham.y_max = thread->thread_steps;

    thread->bresenham.delta_error = thread->thread_steps + 1;
    thread->bresenham.delta_error_max = thread->encoder_steps + 1;
    thread->bresenham.error = 0;
}

void thread_on_encoder_cb(struct encoder_s *encoder, bool dir, void *arg)
{
    struct thread_desc_s *thread = arg;

    if (!thread->valid)
    {
        return;
    }

    thread->bresenham.error += thread->bresenham.delta_error;
    
    while (thread->bresenham.error >= thread->bresenham.delta_error_max)
    {
        thread->bresenham.error -= thread->bresenham.delta_error_max;
        thread->screw->set_dir(dir != thread->dir);
        thread->screw->make_step();
        thread->bresenham.y++;
    }
    thread->bresenham.x++;

    if (thread->bresenham.x >= thread->bresenham.x_max)
    {
        while (thread->bresenham.y < thread->bresenham.y_max)
        {
            thread->screw->set_dir(dir != thread->dir);
            thread->screw->make_step();
            thread->bresenham.y++;
        }

        thread->bresenham.x = 0;
        thread->bresenham.error = 0;
    }
}
