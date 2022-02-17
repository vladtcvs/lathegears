#include <stdio.h>

#include "encoder.h"
#include "screw.h"
#include "threads.h"

#include "control.h"


static void select_thread(struct control_state_s *state, int id)
{
    if (id > 0 && id < MAX_THREADS)
    {
        if (state->thread_defined[id])
        {
            encoder_register_callback(state->spindel_encoder, thread_on_encoder_cb, &state->threads[id]);
            thread_start(&state->threads[id]);
        }
        else
        {
            encoder_register_callback(state->spindel_encoder, NULL, NULL);
        }
    }
    else
    {
        encoder_register_callback(state->spindel_encoder, NULL, NULL);
    }
}

void control_init(struct control_state_s *state,
		  struct encoder_s *spindel_encoder,
		  struct screw_desc_s *main_screw)
{
    state->spindel_encoder = spindel_encoder;
    state->main_screw = main_screw;
}

bool control_register_thread(struct control_state_s *state, real pitch, bool right)
{
    int i;
    for (i = 0; i < MAX_THREADS; i++)
    {
        if (state->thread_defined[i] == false)
        {
            thread_init(&state->threads[i], pitch, right, state->main_screw, state->spindel_encoder);
            state->thread_defined[i] = true;
            return true;
        }
    }
    return false;
}

size_t control_threads(struct control_state_s *state, struct thread_desc_s **_threads, bool **_defined)
{
    *_threads = state->threads;
    *_defined = state->thread_defined;
    return MAX_THREADS;
}

bool control_select_thread(struct control_state_s *state, int thread)
{
    if (thread >= 0 && thread < MAX_THREADS)
    {
        state->selected_thread_id = thread;
        return true;
    }
    return false;
}

void control_start_thread(struct control_state_s *state)
{
    select_thread(state, state->selected_thread_id);
}

void control_stop_thread(struct control_state_s *state)
{
    select_thread(state, -1);
}

