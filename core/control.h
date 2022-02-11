#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "common.h"
#include "threads.h"

void control_init(int encoder_steps,
                  int screw_steps,
                  real screw_pitch,
                  bool screw_right,
                  void (*set_dir)(bool dir),
                  void (*make_step)(void),
                  void (*start_timer)(void),
                  void (*stop_timer)(void),
		  int multiplicator_ratio,
		  uint32_t multiplicator_max_ticks);

bool control_register_thread(real pitch, bool right);
size_t control_threads(struct thread_desc_s **_threads, bool **_defined);
bool control_select_thread(int thread);
void control_start_thread(void);
void control_stop_thread(void);

void control_multiplyer_timer_tick(void);
void control_encoder_tick(bool dir);
