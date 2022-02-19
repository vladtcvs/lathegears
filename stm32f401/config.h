#pragma once

#define STM32F4

#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/gpio.h>

#define SPINDEL_ENCODER_STEPS (600*3*4)
#define SCREW_STEPS (200*4*3)
#define SCREW_PITCH 2.0

#define LED_PORT  GPIOC
#define LED_PIN   GPIO13

#define STEP_PORT GPIOA
#define STEP_PIN  GPIO2

#define DIR_PORT  GPIOA
#define DIR_PIN   GPIO1

#define EN_PORT   GPIOA
#define EN_PIN    GPIO0

#define PH_A_PORT GPIOB
#define PH_A_PIN  GPIO13

#define PH_B_PORT GPIOB
#define PH_B_PIN  GPIO12

#define IFACE_INT_PORT GPIOB
#define IFACE_INT_PIN  GPIO7

#define IFACE_ENC_A_PORT GPIOB
#define IFACE_ENC_A_PIN  GPIO6

#define IFACE_ENC_B_PORT GPIOB
#define IFACE_ENC_B_PIN  GPIO5

#define BUTTONS_PCF8574 0x20
#define EEPROM_24LC256  0x50
#define DISPLAY_SSD1306 0x3C


#define I2C_ID I2C1
#define I2C_RCC RCC_I2C1

#define I2C_SDA_PORT GPIOB
#define I2C_SDA_PIN  GPIO9
#define I2C_SDA_AF   GPIO_AF4

#define I2C_SCL_PORT GPIOB
#define I2C_SCL_PIN  GPIO8
#define I2C_SCL_AF   GPIO_AF4
