#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "common.h"
#include "threads.h"

struct control_state_s
{
    struct thread_desc_s threads[MAX_THREADS];
    bool thread_defined[MAX_THREADS];
    int  selected_thread_id;

    struct encoder_s     *spindel_encoder;
    struct screw_desc_s  *main_screw;
};


void control_init(struct control_state_s *state,
		  struct encoder_s *spindel_encoder,
		  struct screw_desc_s *main_screw);

bool control_register_thread(struct control_state_s *state, real pitch, bool right);
size_t control_threads(struct control_state_s *state, struct thread_desc_s **_threads, bool **_defined);
bool control_select_thread(struct control_state_s *state, int thread);
void control_start_thread(struct control_state_s *state);
void control_stop_thread(struct control_state_s *state);

