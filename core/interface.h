#pragma once

#include "encoder.h"
#include "control.h"

enum interface_state_e
{
    INTERFACE_SELECT = 0,
    INTERFACE_RUNNING,
};

struct interface_state_s
{
    struct control_state_s *control;
    struct encoder_s *input_encoder;
    void (*display_thread)(int id, real pitch, bool right);
    enum interface_state_e state;
};

void interface_init(struct interface_state_s *state);
void interface_print_state(struct interface_state_s *state);
void interface_reset_button(struct interface_state_s *state, bool pressed);
void interface_stop_button(struct interface_state_s *state, bool pressed);
void interface_start_button(struct interface_state_s *state, bool pressed);

