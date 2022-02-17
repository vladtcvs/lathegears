#pragma once

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

