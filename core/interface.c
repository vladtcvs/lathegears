#include "interface.h"
#include "control.h"

static struct encoder_s encoder;
static struct interface_control_s iface;

void interface_start_button(bool pressed)
{
    control_select_thread(iface.thread_id);
    control_start_thread();
}

void interface_stop_button(bool pressed)
{
    control_stop_thread();
}

void interface_reset_button(bool pressed)
{
    iface.thread_id = 0;
    control_select_thread(iface.thread_id);
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

void interface_encoder_cb(struct encoder_s *encoder, bool right, void *arg)
{
    struct interface_control_s *iface = arg;

    struct thread_desc_s *threads;
    bool *defined;

    size_t maxthreads = control_threads(&threads, &defined);

    if (right)
    {
        iface->thread_id = next_thread(iface->thread_id, defined, maxthreads);
    }
    else
    {
        iface->thread_id = prev_thread(iface->thread_id, defined, maxthreads);
    }    
}

void interface_init(void)
{
    iface.encoder = &encoder;
    encoder_register_callback(&encoder, interface_encoder_cb, &iface);
}

void interface_encoder(bool right)
{
    encoder_pulse(&encoder, right);
}
