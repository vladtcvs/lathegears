#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "common.h"

void control_init(int encoder_steps, int screw_steps, real screw_pitch, bool screw_right, void (*set_dir)(bool dir), void (*make_step)(void));

bool control_register_thread(real pitch, bool right);
bool control_select_thread(int thread);
void control_start_thread(void);
void control_stop_thread(void);

void control_multiplyer_timer_tick(void);
void control_encoder_tick(bool dir);
