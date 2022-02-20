#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

bool display_init(uint32_t i2c, uint8_t addr,
                  void (*i2c_send_bytes)(uint32_t i2c, uint8_t addr, const uint8_t *data, size_t len, bool *ok),
                  void (*i2c_read_bytes)(uint32_t i2c, uint8_t addr, uint8_t *data, size_t len, bool *ok));

void display_print_state(bool running, int threadid, float pitch, bool right);

void display_show(const char *text, int len);
