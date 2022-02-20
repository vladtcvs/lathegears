#include "interface.h"
#include "control.h"

static void interface_encoder_cb(struct encoder_s *encoder, bool right, void *arg);

void interface_print_state(struct interface_state_s *state)
{
    int thread_id = state->control->selected_thread_id;

    struct thread_desc_s *threads;
    bool *defined;
    control_threads(state->control, &threads, &defined);

    real pitch = threads[thread_id].pitch;
    bool right = threads[thread_id].right;
    state->display_thread(state->control->selected_thread_id, pitch, right);
}

void interface_init(struct interface_state_s *state)
{
    encoder_register_callback(state->input_encoder, interface_encoder_cb, state);
    state->state = INTERFACE_SELECT;
}

void interface_reset_button(struct interface_state_s *state, bool pressed)
{
    state->state = INTERFACE_SELECT;
    control_stop_thread(state->control);
    control_select_thread(state->control, 0);

    interface_print_state(state);
}

void interface_stop_button(struct interface_state_s *state, bool pressed)
{
    state->state = INTERFACE_SELECT;
    control_stop_thread(state->control);

    interface_print_state(state);
}

void interface_start_button(struct interface_state_s *state, bool pressed)
{
    state->state = INTERFACE_RUNNING;
    control_start_thread(state->control);

    interface_print_state(state);
}

static int next_thread(int id, const bool *defined, size_t maxthreads)
{
    id++;
    id %= maxthreads;
    while (defined[id] == false)
    {
        id++;
        id %= maxthreads;
    }
    return id;
}

static int prev_thread(int id, const bool *defined, size_t maxthreads)
{
    id--;
    if (id == -1)
        id = maxthreads - 1;
    while (defined[id] == false)
    {
        id--;
        if (id == -1)
            id = maxthreads - 1;
    }
    return id;
}

static void interface_encoder_cb(struct encoder_s *encoder, bool right, void *arg)
{
    struct interface_state_s *iface = arg;

    if (iface->state == INTERFACE_SELECT)
    {
        struct thread_desc_s *threads;
        bool *defined;

        size_t maxthreads = control_threads(iface->control, &threads, &defined);

        int tid; 
        if (right)
        {
            tid = next_thread(iface->control->selected_thread_id, defined, maxthreads);
        }
        else
        {
            tid = prev_thread(iface->control->selected_thread_id, defined, maxthreads);
        }

        control_select_thread(iface->control, tid);
        interface_print_state(iface);
    }
}

