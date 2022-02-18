#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include <libopencm3/stm32/i2c.h>

void i2c_init(void);
void i2c_send_bytes(uint32_t i2c, uint8_t addr, const uint8_t *data, size_t len, bool *ok);
void i2c_read_bytes(uint32_t i2c, uint8_t addr, uint8_t *data, size_t len, bool *ok);
