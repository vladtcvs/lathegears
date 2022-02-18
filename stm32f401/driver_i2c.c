#define STM32F4

#include "config.h"
#include "driver_i2c.h"

#include <stdbool.h>
#include <stdint.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>

static void delay(void)
{
    unsigned long i;
    for (i = 0; i < 1000000UL; i++)
        __asm__("nop");
}

void i2c_swrst(uint32_t i2c)
{
    i2c_peripheral_disable(i2c);

    I2C_CR1(i2c) |= I2C_CR1_SWRST;
    delay();
    I2C_CR1(i2c) &= ~I2C_CR1_SWRST;
    delay();

    i2c_set_standard_mode(i2c);
    i2c_set_clock_frequency(i2c, 4);
    i2c_set_ccr(i2c, 35);
    i2c_set_trise(i2c, 43);
    i2c_peripheral_enable(i2c);
}

void i2c_init(void)
{
    // Config I2C
    gpio_mode_setup(I2C_SDA_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, I2C_SDA_PIN);
    gpio_mode_setup(I2C_SCL_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, I2C_SCL_PIN);

    gpio_set_output_options(I2C_SDA_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, I2C_SDA_PIN);
    gpio_set_output_options(I2C_SCL_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, I2C_SCL_PIN);

    gpio_set_af(I2C_SDA_PORT, I2C_SDA_AF, I2C_SDA_PIN);
    gpio_set_af(I2C_SCL_PORT, I2C_SCL_AF, I2C_SCL_PIN);

    /* Enable I2C1 clock */
    rcc_periph_clock_enable(I2C_RCC);

    delay();

    rcc_get_i2c_clk_freq(I2C_ID);

    i2c_peripheral_disable(I2C_ID);

    i2c_reset(I2C_ID);
    i2c_swrst(I2C_ID);

    i2c_peripheral_enable(I2C_ID);
    i2c_set_own_7bit_slave_address(I2C_ID, 0x00);
}


#define WAIT_CONDITION(condition, retries)   do {                                   \
                                                int cnt = 0;                        \
                                                failed = true;                      \
                                                for (cnt = 0; cnt < retries; cnt++) \
                                                {                                   \
                                                    if (condition)                  \
                                                    {                               \
                                                        failed = false;             \
                                                        break;                      \
                                                    }                               \
                                                }                                   \
                                            } while(0)

#define RETRY(i2c)  {                                   \
                        i2c_send_stop(i2c);             \
                        i2c_swrst(i2c);                 \
                        tries++;                        \
                        continue;                       \
                    }



void i2c_send_bytes(uint32_t i2c, uint8_t addr, const uint8_t *data, size_t len, bool *ok)
{
    *ok = false;

    int tries = 0;
    while (tries < 10)
    {
        bool failed;
        
        WAIT_CONDITION(!(I2C_SR2(i2c) & I2C_SR2_BUSY), 100000);
        if (failed)
            RETRY(i2c);

        i2c_send_start(i2c);

        /* Wait for the end of the start condition, master mode selected, and BUSY bit set */
        WAIT_CONDITION((I2C_SR1(i2c) & I2C_SR1_SB) && (I2C_SR2(i2c) & I2C_SR2_MSL) && (I2C_SR2(i2c) & I2C_SR2_BUSY), 10000);
        if (failed)
            RETRY(i2c);

        i2c_send_7bit_address(i2c, addr, I2C_WRITE);

        /* Waiting for address is transferred. */
        WAIT_CONDITION(I2C_SR1(i2c) & I2C_SR1_ADDR, 10000);
        if (failed)
            RETRY(i2c);

        uint32_t reg32 = I2C_SR2(i2c);

        int i;
        for (i = 0; i < len; i++)
        {
            i2c_send_data(i2c, data[i]);

            WAIT_CONDITION(I2C_SR1(i2c) & I2C_SR1_BTF, 10000);
            if (failed)
                break;
        }

        if (failed)
            RETRY(i2c);

        *ok = true;
        break;
    }

    i2c_send_stop(i2c);
}

void i2c_read_bytes(uint32_t i2c, uint8_t addr, uint8_t *data, size_t len, bool *ok)
{
    i2c_transfer7(i2c, addr, NULL, 0, data, len);
    *ok = true;
}
