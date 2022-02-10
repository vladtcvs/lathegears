#pragma once

#include "encoder.h"
#include "control.h"

struct interface_control_s
{
    struct encoder_s *encoder;
    int thread_id;
};

void interface_init(void);
void interface_reset_button(bool pressed);
void interface_stop_button(bool pressed);
void interface_start_button(bool pressed);
void interface_encoder(bool right);
