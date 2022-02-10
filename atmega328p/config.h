#pragma once

#define SPINDEL_ENCODER_STEPS 100
#define SCREW_STEPS (200*2*3)
#define SCREW_PITCH 2.0

#define LED_DDR   DDRB
#define LED_PORT  PORTB
#define LED_PIN   5

#define STEP_DDR  DDRD
#define STEP_PORT PORTD
#define STEP_PIN  4

#define DIR_DDR   DDRD
#define DIR_PORT  PORTD
#define DIR_PIN   5

#define PH_A_DDR  DDRD
#define PH_A_PORT PORTD
#define PH_A_PIN  2

#define PH_B_DDR  DDRD
#define PH_B_PORT PORTD
#define PH_B_PIN  3

#define START_BTN_DDR    DDRB
#define START_BTN_PORT   PORTD
#define START_BTN_PIN    0

#define STOP_BTN_DDR     DDRB
#define STOP_BTN_PORT    PORTD
#define STOP_BTN_PIN     1

#define RESET_BTN_DDR    DDRB
#define RESET_BTN_PORT   PORTB
#define RESET_BTN_PIN    2

#define IFACE_ENC_A_DDR  DDRD
#define IFACE_ENC_A_PORT PORTD
#define IFACE_ENC_A_PIN  6

#define IFACE_ENC_B_DDR  DDRD
#define IFACE_ENC_B_PORT PORTD
#define IFACE_ENC_B_PIN  7
