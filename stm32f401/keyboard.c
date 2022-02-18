#define STM32F4

#include <stdbool.h>
#include <stdint.h>

#include "config.h"
#include "driver_i2c.h"

#include "interface.h"

static void pcf8574_write(uint32_t i2c, uint8_t addr, uint8_t data)
{
    bool ok;
    i2c_send_bytes(i2c, addr, &data, 1, &ok);
}

static uint8_t pcf8574_read(uint32_t i2c, uint8_t addr)
{
    uint8_t data;
    bool ok;
    i2c_read_bytes(i2c, addr, &data, 1, &ok);
    return data;
}

uint32_t buttons_read(void)
{
    uint32_t data = pcf8574_read(I2C_ID, BUTTONS_PCF8574) & 0x3F;
    return data;
}

void buttons_init(void)
{
    pcf8574_write(I2C_ID, BUTTONS_PCF8574, 0xFF);
}

