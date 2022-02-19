#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

void i2c_init(void);

bool i2c_detect_device(uint32_t i2c, uint8_t addr);
size_t i2c_list_devices(uint32_t i2c, uint8_t *devices);

void i2c_send_bytes(uint32_t i2c, uint8_t addr, const uint8_t *data, size_t len, bool *ok);
void i2c_read_bytes(uint32_t i2c, uint8_t addr, uint8_t *data, size_t len, bool *ok);
