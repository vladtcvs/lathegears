#pragma once

#include "encoder.h"

void encoder_multiplicator_init(struct encoder_s *mult, struct encoder_s *source, int ratio, uint32_t max_ticks);
void encoder_multiplicator_timer_tick(void);
