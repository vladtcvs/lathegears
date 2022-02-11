#include <stdio.h>

#include "encoder.h"
#include "screw.h"
#include "threads.h"

#include "encoder_multiplicator.h"
#include "control.h"

void (*_start_timer)(void);
void (*_stop_timer)(void);

struct encoder_s spindel_encoder;
struct encoder_s spindel_multiplied_encoder;

struct screw_desc_s main_screw;

struct thread_desc_s threads[MAX_THREADS];
bool thread_defined[MAX_THREADS] = {false};

struct control_state_s
{
    int selected_thread;
    bool running_thread;
};

struct control_state_s state;

static void select_thread(int id)
{
    if (id > 0 && id < MAX_THREADS)
    {
        if (thread_defined[id])
        {
            encoder_register_callback(&spindel_multiplied_encoder, thread_on_encoder_cb, &threads[id]);
            thread_start(&threads[id]);
        }
        else
        {
            encoder_register_callback(&spindel_multiplied_encoder, NULL, NULL);
        }
    }
    else
    {
        encoder_register_callback(&spindel_multiplied_encoder, NULL, NULL);
    }
}

void control_init(int encoder_steps,
                  int screw_steps,
                  real screw_pitch,
                  bool screw_right,
                  void (*set_dir)(bool dir),
                  void (*make_step)(void),
                  void (*start_timer)(void),
                  void (*stop_timer)(void),
		  int multiplicator_ratio,
		  uint32_t multiplicator_max_ticks)
{
    main_screw.dir = screw_right;
    main_screw.pitch = screw_pitch;
    main_screw.steps = screw_steps;

    main_screw.set_dir = set_dir;
    main_screw.make_step = make_step;

    _start_timer = start_timer;
    _stop_timer = stop_timer;

    encoder_init(&spindel_encoder, encoder_steps);
    encoder_multiplicator_init(&spindel_multiplied_encoder, &spindel_encoder, multiplicator_ratio, multiplicator_max_ticks);
}

bool control_register_thread(real pitch, bool right)
{
    int i;
    for (i = 0; i < MAX_THREADS; i++)
    {
        if (thread_defined[i] == false)
        {
            thread_init(&threads[i], pitch, right, &main_screw, &spindel_multiplied_encoder);
            thread_defined[i] = true;
            return true;
        }
    }
    return false;
}

size_t control_threads(struct thread_desc_s **_threads, bool **_defined)
{
    *_threads = threads;
    *_defined = thread_defined;
    return MAX_THREADS;
}

bool control_select_thread(int thread)
{
    if (thread >= 0 && thread < MAX_THREADS)
    {
        state.selected_thread = thread;
        return true;
    }
    return false;
}

void control_start_thread(void)
{
    state.running_thread = true;
    select_thread(state.selected_thread);
    _start_timer();
}

void control_stop_thread(void)
{
    _stop_timer();
    select_thread(-1);
}

void control_multiplyer_timer_tick(void)
{
    if (state.running_thread)
        encoder_multiplicator_timer_tick();
}

void control_encoder_tick(bool dir)
{
    encoder_pulse(&spindel_encoder, dir);
}
